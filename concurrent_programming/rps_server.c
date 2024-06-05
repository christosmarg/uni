#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int srv(int);
static void sighandler(int);
static void usage(void);

static volatile sig_atomic_t f_quit = 0;

static int
srv(int fd)
{
	int quit;

	for (;;) {
		if (recv(fd, &quit, sizeof(quit), 0) < 0)
			break;
		if (quit) {
			printf("%s(): quit triggered\n", __func__);
			break;
		}
	}

	return (0);
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
	int sfd;
	int cfd;
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

	for (;;) {
		/* We caught a termination signal. */
		if (f_quit)
			break;
		if ((cfd = accept(sfd, NULL, NULL)) < 0)
			continue;
		printf("[%s] client connected: %d\n", getprogname(), cfd);
		/* 
		 * Create a child process to serve the client so the parent can
		 * continue waiting for another client to serve.
		 */
		switch (fork()) {
		case -1:
			err(1, "fork");
		case 0:
			if (srv(cfd) < 0)
				warnx("srv failed");
			printf("[%s] client disconnected: %d\n",
			    getprogname(), cfd);
			_exit(0);
		default:
			close(cfd);
		}
	}

	/* Will get here only if a termination signal is caught. */
	close(sfd);
	close(cfd);

	return (0);
}
