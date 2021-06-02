#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 3 (server) / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex3_server.c -o ex3_server`
 */

/* Results to be sent back to the client. */
struct pack_res {
	char str[32];
	float avg;
};

struct foo {
	int cfd;
	int nsucc;
	int ntotal;
};

static int srv(struct foo *);
static void sighandler(int);
static void *emalloc(size_t);

static char *argv0;
/* Gets set only if a termination signal is caught. */
static volatile sig_atomic_t f_quit = 0;

static int
srv(struct foo *foo)
{
	struct foo *f;
	struct pack_res *res;
	int *arr;
	int i, n, sum;
	int rc;
	char cont;

	f = (struct foo *)foo;
	/*
	 * The return code is -1 (error) by default so that we don't
	 * need to set it everytime an error occurs in the main loop.
	 * If there are no errors, `rc` will be set to 0 (success) right
	 * after the loop.
	 */
	rc = -1;
	for (;;) {
		if (recv(f->cfd, &n, sizeof(int), 0) < 0)
			goto fail;
		arr = emalloc(n * sizeof(int));
		if (recv(f->cfd, arr, n * sizeof(int), 0) < 0)
			goto fail;
		res = emalloc(sizeof(struct pack_res));

		printf("cfd: %d\tn: %d\n", f->cfd, n);
		for (i = 0, sum = 0; i < n; i++) {
			printf("cfd: %d\tarr[%d]: %d\n", f->cfd, i, arr[i]);
			sum += arr[i];
		}
		free(arr);
		/* 
		 * When we go to `fail:`, `gcc` for some reason double frees if 
		 * we don't manually set it to NULL, even though we explicitly 
		 * check for NULL first...
		 */
		arr = NULL;

		if ((res->avg = sum / (float)n) > 10.0f) {
			(void)strncpy(res->str, "sequence: ok",
			    sizeof(res->str) - 1);
			f->nsucc++;
		} else
			(void)strncpy(res->str, "sequence: failed",
			    sizeof(res->str) - 1);
		if (send(f->cfd, res, sizeof(struct pack_res), 0) < 0)
			goto fail;
		f->ntotal++;
		printf("[%s] success: %d: total: %d\n",
		    argv0, f->nsucc, f->ntotal);

		if (recv(f->cfd, &cont, 1, 0) < 0)
			goto fail;
		if (cont == 'n')
			break;
	}
	rc = 0;

fail:
	printf("[%s] connection with client %d closed\n", argv0, f->cfd);
	(void)close(f->cfd);
	if (arr != NULL)
		free(arr);
	if (res != NULL)
		free(res);

	return rc;
}

static void
sighandler(int sig)
{
	f_quit = 1;
}

static void *
emalloc(size_t nb)
{
	void *p;

	if ((p = malloc(nb)) == NULL)
		err(1, "malloc");

	return p;
}

static void
usage(void)
{
	fprintf(stderr, "usage: %1$s [-b backlog] [-s sockfile]\n"
	    "       %1$s -i [-p port] [-b backlog] [-s sockfile] hostname\n"
	    "       %1$s -i [-p port] [-b backlog] [-s sockfile] ipv4_addr\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct foo *f;
	struct sockaddr_un sun;
	struct sockaddr_in sin;
	struct hostent *hp;
	struct sigaction sa;
	char *sockfile = "/tmp/cool.sock";
	int sfd;
	int backlog = 10;
	int port = 9999;
	int iflag, uflag, sockflags;
	char ch;

	argv0 = *argv;
	/* Run in the UNIX domain by default. */
	uflag = 1;
	iflag = 0;

	while ((ch = getopt(argc, argv, "b:ip:s:")) != -1) {
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
		case 'i':
			/* Run the server on the internet domain. */
			iflag = 1;
			uflag = 0;
			break;
		case 'p':
			/* Choose custom port but don't use a well-known port. */
			if ((port = atoi(optarg)) < 1024)
				errx(1, "can't use port number < 1024");
			break;
		case 's':
			sockfile = optarg;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* 
	 * If we're on the internet domain, we also need a hostname 
	 * or an IPv4 address. 
	 */
	if (iflag && argc < 1)
		usage();
	/*
	 * Handle termination signals so we don't exit abnormally
	 * (i.e without cleaning up resources).
	 */
	(void)memset(&sa, 0, sizeof(sa));
	(void)sigfillset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		err(1, "sigaction(SIGINT)");
	if (sigaction(SIGTERM, &sa, NULL) < 0)
		err(1, "sigaction(SIGTERM)");

	/* Set up the socket for use in the Internet domain. */
	if (iflag) {
		if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			err(1, "socket(AF_INET)");
		(void)memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		/* Convert the port number to network bytes. */
		sin.sin_port = htons(port);

		/* 
		 * We'll try and see if the input is an IPv4 address. If
		 * inet_aton(3) does not fail, the user passed an IPv4 address.
		 * However if inet_addr(3) fail, we'll assume the user passed
		 * an hostname. That lets us use both hostnames and IPv4
		 * addresses as arguments.
		 */
		if (!inet_aton(*argv, &sin.sin_addr)) {
			/* 
			 * Get host info by hostname. The host's IPv4 address
			 * will be written to `hp->h_addr`.
			 */
			if ((hp = gethostbyname(*argv)) == NULL)
				errx(1, "gethostbyname(%s) failed", *argv);
			(void)memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
		}
		if (bind(sfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
			err(1, "bind");

		printf("Socket: %s\nDomain: AF_INET\nIPv4: %s\n"
		    "Port: %d\nBacklog: %d\n", 
		    sockfile, inet_ntoa(sin.sin_addr), port, backlog);
	/* Set up the socket for use in the UNIX domain. */
	} else if (uflag) {
		if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
			err(1, "socket(AF_UNIX)");
		(void)memset(&sun, 0, sizeof(sun));
		sun.sun_family = AF_UNIX;
		(void)strncpy(sun.sun_path, sockfile, sizeof(sun.sun_path) - 1);
		if (bind(sfd, (struct sockaddr *)&sun, sizeof(sun)) < 0)
			err(1, "bind");

		printf("Socket: %s\nDomain: AF_UNIX\nBacklog: %d\n",
		    sockfile, backlog);
	}
	if (listen(sfd, backlog) < 0)
		err(1, "listen");

	f = emalloc(sizeof(struct foo));
	f->nsucc = 0;
	f->ntotal = 0;

	for (;;) {
		/* We caught a termination signal. */
		if (f_quit)
			break;
		/*
		 * accept(2)'s `addr` and `addrlen` arguments can be NULL if
		 * we don't care about the address information of the client.
		 */
		if ((f->cfd = accept(sfd, NULL, NULL)) < 0)
			continue;
		printf("[%s] accepted client: %d\n", argv0, f->cfd);
		/* 
		 * Create a child process to serve the client so the parent can
		 * continue waiting for another client to serve.
		 */
		switch (fork()) {
		case -1:
			err(1, "fork");
		case 0:
			if (srv(f) < 0)
				warnx("srv failed");
			_exit(0);
		default:
			(void)close(f->cfd);
		}

	}
	/* Will get here only if a termination signal is caught. */
	(void)close(f->cfd);
	(void)close(sfd);
	(void)unlink(sockfile);
	free(f);

	return 0;
}
