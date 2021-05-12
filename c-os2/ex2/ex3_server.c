#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 3 (server) / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex3_server.c -lpthread -o ex3_server`
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
static void die(const char *);

static char *argv0;
static volatile sig_atomic_t f_quit = 0;

static int
srv(struct foo *foo)
{
	struct foo *f;
	struct pack_res *res;
	int *arr;
	int i, n, sum;
	int rc;
	char cont = 'y';

	/*
	 * The return code is -1 (error) by default so that we don't
	 * need to set it everytime an error occurs in the main loop.
	 * If there are no errors, `rc` will be set to 0 (success) right
	 * after the loop.
	 */
	rc = -1;
	f = (struct foo *)foo;
	while (cont != 'n') {
		if (recv(f->cfd, &n, sizeof(int), 0) == -1)
			goto exit;
		arr = emalloc(n * sizeof(int));
		if (recv(f->cfd, arr, n * sizeof(int), 0) == -1)
			goto exit;
		res = emalloc(sizeof(struct pack_res));
		printf("cfd: %d\tn: %d\n", f->cfd, n);
		for (i = 0, sum = 0; i < n; i++) {
			printf("cfd: %d\tarr[%d]: %d\n", f->cfd, i, arr[i]);
			sum += arr[i];
		}

		if ((res->avg = sum / (float)n) > 10.0f) {
			(void)strncpy(res->str, "sequence: ok",
			    sizeof(res->str) - 1);
			f->nsucc++;
		} else
			(void)strncpy(res->str, "sequence: failed",
			    sizeof(res->str) - 1);
		if (send(f->cfd, res, sizeof(struct pack_res), 0) == -1)
			goto exit;
		f->ntotal++;
		printf("[%s] success: %d: total: %d\n",
		    argv0, f->nsucc, f->ntotal);

		if (recv(f->cfd, &cont, 1, 0) == -1)
			goto exit;
		free(arr);
	}
	rc = 0;

exit:
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
		die("malloc");

	return p;
}

static void
die(const char *str)
{
	(void)fprintf(stderr, "%s: ", argv0);
	perror(str);
	exit(1);
}

static void
usage(void)
{
	(void)fprintf(stderr, "usage: %s [-b backlog] [-s sockfile]\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct sockaddr_un sun;
	struct foo *f;
	struct sigaction sa;
	char *sockfile = "/tmp/cool.sock";
	int sfd;
	int backlog = 10;
	char ch;

	argv0 = *argv;
	if ((ch = getopt(argc, argv, "b:s:")) != -1) {
		switch (ch) {
		case 'b';
			if ((backlog = atoi(optarg)) < 1)
				usage();
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
	 * Handle termination signals so we don't exit abnormally
	 * (i.e without cleaning up resources).
	 */
	(void)memset(&sa, 0, sizeof(sa));
	(void)sigemptyset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGHUP, &sa, NULL) == -1)
		die("sigaction: SIGHUP");
	if (sigaction(SIGINT, &sa, NULL) == -1)
		die("sigaction: SIGINT");
	if (sigaction(SIGTERM, &sa, NULL) == -1)
		die("sigaction: SIGTERM");

	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		die("socket");
	(void)memset(&sun, 0, sizeof(sun));
	sun.sun_family = AF_UNIX;
	(void)strncpy(sun.sun_path, sockfile, sizeof(sun.sun_path) - 1);

	if (bind(sfd, (struct sockaddr *)&sun, sizeof(sun)) == -1)
		die("bind");
	if (listen(sfd, BACKLOG) == -1)
		die("listen");

	f = emalloc(sizeof(struct foo));
	f->nsucc = 0;
	f->ntotal = 0;

	for (;;) {
		/* FIXME: blocked by accept */
		if (f_quit)
			break;
		/*
		 * accept(2)'s `addr` and `addrlen` arguments can be NULL if
		 * we don't care about the address information of the client.
		 */
		if ((f->cfd = accept(sfd, NULL, NULL)) == -1)
			continue;
		printf("[%s] accepted client: %d\n", argv0, f->cfd);
		switch (fork()) {
		case -1:
			die("fork");
		case 0:
			if (srv(f) == -1)
				perror("srv");
			_exit(0);
		default:
			(void)close(f->cfd);
		}

	}

	/* Will get here only if a termination signal is caught. */
	(void)close(f->cfd);
	(void)close(sfd);
	free(f);
	/*
	 * bind(2)'s man page states that the socket should be deleted when
	 * it's no longer needed.
	 */
	(void)unlink(sockfile);

	return 0;
}
