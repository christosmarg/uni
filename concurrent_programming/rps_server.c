#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "extern.h"

struct client {
	int fd;
	int id;
	char name[NAME_LEN];
	int move;
	int nplays;
	int nwins;
	struct client *opponent;
};

static void remove_client(struct client *);
static int srv(int);
static void sighandler(int);
static void usage(void);

static int *ids;
static int *nclients;
static struct client *clients;
static volatile sig_atomic_t f_quit = 0;

static void
remove_client(struct client *c)
{
	struct client *cp;
	int i;

	if (c->id < 1)
		return;
	for (i = 0; i < CLIENTS_MAX; i++) {
		cp = &clients[i];
		if (cp == c) {
			printf("%s: client disconnected: %s#%d (fd=%d)\n",
			    getprogname(), cp->name, cp->id, cp->fd);
			close(cp->fd);
			memset(cp, 0, sizeof(*cp));
			(*nclients)--;
			break;
		}
	}
}

static int
srv(int fd)
{
	struct client *c, *cp;
	char cmd[CMD_LEN], buf[BUF_LEN];
	size_t len;
	int rc = 0, i, tmp, quit, id;

	c = &clients[*nclients];
	memset(c, 0, sizeof(*c));
	c->fd = fd;
	c->id = ++(*ids);
	c->move = -1;

	(*nclients)++;

	if (recv(c->fd, c->name, sizeof(c->name), 0) < 0) {
		warn("recv(%d, nick)", c->fd);
		remove_client(c);
		return (-1);
	}

	printf("%s: active clients=%d\n", getprogname(), *nclients);
	printf("%s: client connected: %s#%d (fd=%d)\n",
	    getprogname(), c->name, c->id, c->fd);

	for (;;) {
		memset(buf, 0, sizeof(buf));
		tmp = recv(c->fd, cmd, sizeof(cmd), 0);
		if (tmp < 0) {
			warn("recv(%d, cmd)", c->fd);
			rc = -1;
			break;
		} else if (tmp == 0)
			break;

		if (strcmp(cmd, "challenge") == 0) {
			if (recv(c->fd, &id, sizeof(id), 0) < 0) {
				warn("recv(%d, challenge, id)", c->fd);
				rc = -1;
				break;
			}
			if (recv(c->fd, &c->move, sizeof(c->move), 0) < 0) {
				warn("recv(%d, challenge, move)", c->fd);
				rc = -1;
				break;
			}
			if (c->id == id) {
				warnx("%s tried to challenge themselves",
				    c->name);
				continue;
			}
			cp = NULL;
			for (i = 0; i < CLIENTS_MAX; i++) {
				cp = &clients[i];
				if (cp->id > 0 && cp->id == id)
					break;
				cp = NULL;
			}
			/* TODO add lock */
			if (cp == NULL) {
				warnx("id=%d not found", id);
				continue;
			}
			if (cp->opponent != NULL) {
				warnx("%s is already challenged", cp->name);
				continue;
			}
			c->opponent = cp;
			cp->opponent = c;

			printf("%s is challenging %s with %s\n",
			    c->name, cp->name, move2str(c->move));
			for (i = 0; i < MOVE_TIMEOUT; i++) {
				if (c->opponent != NULL)
					sleep(1);
				else
					break;
			}
			printf("%s woke up\n", c->name);
			if (c->opponent != NULL) {
				printf("%s didn't make a move\n", c->opponent->name);
				c->nwins++;
				c->move = -1;
				c->nplays++;
				c->opponent->move = -1;
				c->opponent->nplays++;
				c->opponent->opponent = NULL;
				c->opponent = NULL;
			}
		} else if (strcmp(cmd, "accept") == 0) {
			if (recv(c->fd, &c->move, sizeof(c->move), 0) < 0) {
				warn("recv(%d, accept)", c->fd);
				rc = -1;
				break;
			}

			if (c->opponent == NULL) {
				warnx("%s: cannot play when unchallenged",
				    c->name);
				continue;
			}

			switch (c->move) {
			case MOVE_ROCK:
				if (c->opponent->move == MOVE_SCISSOR)
					c->nwins++;
				else if (c->opponent->move == MOVE_PAPER)
					c->opponent->nwins++;
				break;
			case MOVE_PAPER:
				if (c->opponent->move == MOVE_ROCK)
					c->nwins++;
				else if (c->opponent->move == MOVE_SCISSOR)
					c->opponent->nwins++;
				break;
			case MOVE_SCISSOR:
				if (c->opponent->move == MOVE_PAPER)
					c->nwins++;
				else if (c->opponent->move == MOVE_ROCK)
					c->opponent->nwins++;
				break;
			default:
				warnx("invalid move: %s", move2str(c->move));
				continue;
			}
			printf("%s (%d) - %s (%d)\n",
			    c->name, c->nwins,
			    c->opponent->name, c->opponent->nwins);

			c->move = -1;
			c->nplays++;
			c->opponent->move = -1;
			c->opponent->nplays++;
			c->opponent->opponent = NULL;
			c->opponent = NULL;
		} else if (strcmp(cmd, "msg") == 0) {
			if (recv(c->fd, &len, sizeof(len), 0) < 0) {
				warn("recv(%d, msg, len)", c->fd);
				rc = -1;
				break;
			}
			if (len < 0 || len > BUF_LEN) {
				warnx("invalid length: %ld", len);
				continue;
			}
			if (recv(c->fd, buf, len, 0) < 0) {
				warn("recv(%d, msg, msg)", c->fd);
				rc = -1;
				break;
			}
			buf[len] = '\0';
			printf("<%s> %s\n", c->name, buf);
			/* TODO send message to client */
		} else if (strcmp(cmd, "list") == 0) {
			snprintf(buf, sizeof(buf),
			    "ID\tNAME\tPLAYED\tWON\n");
			for (i = 0; i < CLIENTS_MAX; i++) {
				cp = &clients[i];
				if (cp->id == 0)
					continue;
				snprintf(buf + strlen(buf), sizeof(buf),
				    "%d\t%s\t%d\t%d\n",
				    cp->id, cp->name, cp->nplays, cp->nwins);
			}
			if (send(c->fd, buf, sizeof(buf), 0) < 0) {
				warn("send(%d, list)", c->fd);
				rc = -1;
				break;
			}
		} else if (strcmp(cmd, "quit") == 0) {
			break;
		} else {
			warnx("received unknown command: %s", cmd);
		}
	}

	remove_client(c);

	return (rc);
}

static void
sighandler(int sig)
{
	f_quit = 1;
}

static void
usage(void)
{
	fprintf(stderr, "usage: %1$s [-b backlog] [-p port] <hostname|ipv4_addr>\n",
	    getprogname());
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct sockaddr_in sin;
	struct hostent *hp;
	struct sigaction sa;
	int backlog = 10;
	int port = 9999;
	int sfd, cfd;
	int ch, i;

	while ((ch = getopt(argc, argv, "b:p:")) != -1) {
		switch (ch) {
		case 'b':
			/* 
			 * Negative `backlog` value normally requests the
			 * maximum allowable value (HISTORY section of
			 * listen(2)'s FreeBSD man page), but it's better to
			 * not allow it in case the user passes a negative
			 * value accidentally. Also a value of 0 doesn't make
			 * sense, so we don't allow it either.
			 */
			if ((backlog = atoi(optarg)) < 1)
				errx(1, "backlog value must be greater than 1");
			break;
		case 'p':
			/* Choose custom port but don't use a well-known port. */
			if ((port = atoi(optarg)) < 1024)
				errx(1, "can't use port number < 1024");
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* Hostname/IP missing. */
	if (argc < 1)
		usage();

	/*
	 * Handle termination signals so we don't exit abnormally (i.e without
	 * cleaning up resources).
	 */
	memset(&sa, 0, sizeof(sa));
	sigfillset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		err(1, "sigaction(SIGINT)");
	if (sigaction(SIGTERM, &sa, NULL) < 0)
		err(1, "sigaction(SIGTERM)");

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err(1, "socket(AF_INET)");
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	/* Convert the port number to network bytes. */
	sin.sin_port = htons(port);

	/* 
	 * We'll try and see if the input is an IPv4 address. If inet_aton(3)
	 * does not fail, the user did pass an IPv4 address. However if
	 * inet_addr(3) fails, we'll assume the user passed a hostname. If the
	 * hostname was wrong, gethostbyname(3) will fail. That lets us use
	 * both hostnames and IPv4 addresses as arguments.
	 */
	if (!inet_aton(*argv, &sin.sin_addr)) {
		/* 
		 * Get host info by hostname. The host's IPv4 address will be
		 * written to `hp->h_addr`.
		 */
		if ((hp = gethostbyname(*argv)) == NULL)
			errx(1, "gethostbyname(%s) failed", *argv);
		memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
	}
	if (bind(sfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(1, "bind");

	printf("Domain: AF_INET\nIPv4: %s\nPort: %d\nBacklog: %d\n",
	    inet_ntoa(sin.sin_addr), port, backlog);

	if (listen(sfd, backlog) < 0)
		err(1, "listen");

	/* Use mmap(2) that we can modify them from the child. */
	nclients = mmap(NULL, sizeof(*nclients), PROT_READ | PROT_WRITE,
	    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (nclients == MAP_FAILED)
		err(1, "mmap");
	*nclients = 0;

	clients = mmap(NULL, sizeof(struct client) * CLIENTS_MAX,
	    PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (clients == MAP_FAILED)
		err(1, "mmap");
	memset(clients, 0, sizeof(struct client) * CLIENTS_MAX);

	ids = mmap(NULL, sizeof(*ids), PROT_READ | PROT_WRITE,
	    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (ids == MAP_FAILED)
		err(1, "mmap");
	*ids = 0;

	for (;;) {
		/* We caught a termination signal. */
		if (f_quit)
			break;
		/* TODO */
		/*if ((*nclients + 1) >= CLIENTS_MAX)*/
			/*continue;*/
		if ((cfd = accept(sfd, NULL, NULL)) < 0) {
			warn("accept(%d)", cfd);
			continue;
		}
		/* 
		 * Create a child process to serve the client so the parent can
		 * continue waiting for another client to serve.
		 */
		switch (fork()) {
		case -1:
			err(1, "fork");
		case 0:
			if (srv(cfd) < 0)
				warnx("srv(%d) failed", cfd);
			_exit(0);
		default:
			close(cfd);
		}
	}

	/* Will get here only if a termination signal is caught. */
	close(sfd);
	for (i = 0; i < CLIENTS_MAX; i++)
		remove_client(&clients[i]);
	munmap(ids, sizeof(*ids));
	munmap(nclients, sizeof(*nclients));
	munmap(clients, sizeof(struct client) * CLIENTS_MAX);

	return (0);
}
