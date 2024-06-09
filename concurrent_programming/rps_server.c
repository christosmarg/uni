#include <sys/mman.h>
#include <sys/queue.h>
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

struct user {
	int fd;
	int id;
	char name[NAME_LEN];
	int move;
	int nplays;
	int nwins;
	struct user *opponent;
	TAILQ_ENTRY(user) next;
};

static int srv(struct user *);
static void sighandler(int);
static void usage(void);

static volatile sig_atomic_t f_quit = 0;
static int ids = 0;
static int *nusers;
static TAILQ_HEAD(, user) users = TAILQ_HEAD_INITIALIZER(users);

static void
remove_user(struct user *user)
{
	struct user *up;

	while (!TAILQ_EMPTY(&users)) {
		up = TAILQ_FIRST(&users);
		TAILQ_REMOVE(&users, up, next);
		close(up->fd);
		munmap(up, sizeof(struct user));
		break;
	}
}

static int
srv(struct user *user)
{
	struct user *up;
	char cmd[CMD_LEN];
	int rc = 0, tmp, quit, id;

	for (;;) {
		tmp = recv(user->fd, cmd, sizeof(cmd), 0);
		if (tmp < 0) {
			warn("recv(%d, cmd)", user->fd);
			rc = -1;
			break;
		} else if (tmp == 0)
			break;

		if (strcmp(cmd, "challenge") == 0) {
			if (recv(user->fd, &id, sizeof(id), 0) < 0) {
				warn("recv(%d, id)", user->fd);
				rc = -1;
				break;
			}
			up = NULL;
			TAILQ_FOREACH(up, &users, next) {
				if (up->id == id)
					break;
			}
			if (up == NULL) {
				warnx("id=%d not found", id);
				continue;
			}
			if (up->opponent != NULL) {
				warnx("%s is already challenged", up->name);
				continue;
			}
			user->opponent = up;
			up->opponent = user;
			printf("%s is challenging %d\n", user->name, id);
			/* TODO challenge available user */
		} else if (strcmp(cmd, "play") == 0) {
			if (recv(user->fd, &user->move,
			    sizeof(user->move), 0) < 0) {
				warn("recv(%d, play)", user->fd);
				rc = -1;
				break;
			}

			/* Cannot play when unchallenged. */
			if (user->opponent == NULL)
				continue;

			/* Give the opponent 3 seconds to make a move. */
			for (int i = 0; user->opponent->move < 0 &&
			    i < MOVE_TIMEOUT; i++) {
				printf("[%s - %s] %s sleeping\n",
				    user->name, user->opponent->name, user->name);
				sleep(1);
			}

			/* Didn't respond, he lost. */
			if (user->opponent->move < 0) {
				printf("[%s - %s] opponent didn't respond\n",
				    user->name, user->opponent->name);
				user->move = -1;
				user->opponent = NULL;
				/*user->opponent->opponent = NULL;*/
				user->nplays++;
				user->nwins++;
			}

			printf("%s=%d, %s=%d\n", user->name, user->move,
			    user->opponent->name, user->opponent->move);

			switch (user->move) {
			case MOVE_ROCK:
				if (user->opponent->move == MOVE_SCISSOR)
					user->nwins++;
				break;
			case MOVE_PAPER:
				if (user->opponent->move == MOVE_ROCK)
					user->nwins++;
				break;
			case MOVE_SCISSOR:
				if (user->opponent->move == MOVE_PAPER)
					user->nwins++;
				break;
			default:
				warnx("invalid move: %d", user->move);
				continue;
			}
			printf("[%s - %s] = [%d - %d]\n",
			    user->name, user->opponent->name,
			    user->nwins, user->opponent->nwins);

			user->move = -1;
			user->opponent = NULL;
			user->opponent->opponent = NULL;
			user->nplays++;
		} else if (strcmp(cmd, "msg") == 0) {
			/* TODO post message to global chat (list) */
		} else if (strcmp(cmd, "list") == 0) {
			printf("ID\tNAME\tPLAYED\tWON\n");
			TAILQ_FOREACH(up, &users, next) {
				printf("%d\t%s\t%d\t%d\n",
				    up->id, up->name, up->nplays, up->nwins);
			}
			/* TODO send as nvlist */
		} else if (strcmp(cmd, "quit") == 0) {
			break;
		} else {
			warnx("received unknown command: %s", cmd);
		}
	}

	printf("%s: client disconnected: %s#%d (fd=%d)\n",
	    getprogname(), user->name, user->id, user->fd);
	remove_user(user);

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
	struct user *user;
	int backlog = 10;
	int port = 9999;
	int sfd;
	int ch;

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

	/* mmap(2) this that we can modify decrement it from the child. */
	nusers = mmap(NULL, sizeof(*nusers), PROT_READ | PROT_WRITE,
	    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (nusers == MAP_FAILED)
		err(1, "mmap");
	*nusers = 0;

	TAILQ_INIT(&users);

	for (;;) {
		/* We caught a termination signal. */
		if (f_quit)
			break;

		/*
		 * Allocate user structure using mmap(2) so that we can modify
		 * the userlist from the child process.
		 */
		user = mmap(NULL, sizeof(struct user), PROT_READ | PROT_WRITE,
		    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
		if (user == MAP_FAILED)
			err(1, "mmap");

		if ((user->fd = accept(sfd, NULL, NULL)) < 0) {
			warn("accept(%d)", user->fd);
			remove_user(user);
			continue;
		}
		/* Receive nickname and assign ID to user. */
		if (recv(user->fd, user->name, sizeof(user->name), 0) < 0) {
			warn("recv(%d, nick)", user->fd);
			remove_user(user);
			continue;
		}

		user->id = ++ids;
		user->nplays = 0;
		user->nwins = 0;
		user->opponent = NULL;
		TAILQ_INSERT_TAIL(&users, user, next);

		(*nusers)++;

		printf("%s: active users=%d\n", getprogname(), *nusers);
		printf("%s: client connected: %s#%d (fd=%d)\n",
		    getprogname(), user->name, user->id, user->fd);
		/* 
		 * Create a child process to serve the client so the parent can
		 * continue waiting for another client to serve.
		 */
		switch (fork()) {
		case -1:
			err(1, "fork");
		case 0:
			if (srv(user) < 0)
				warnx("srv(%s#%d) failed", user->name, user->id);
			(*nusers)--;
			_exit(0);
		default:
			close(user->fd);
		}
	}

	/* Will get here only if a termination signal is caught. */
	close(sfd);
	remove_user(user);

	return (0);
}
