#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

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
/* Only gets set if a termination signal is caught. */
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

	/*
	 * The return code is -1 (error) by default so that we don't
	 * need to set it everytime an error occurs in the main loop.
	 * If there are no errors, `rc` will be set to 0 (success) right
	 * after the loop.
	 */
	rc = -1;
	f = (struct foo *)foo;
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
		 * If we go to `fail:`, `gcc` for some reason double frees if 
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
	fprintf(stderr, "usage: %s [-b backlog] [-s sockfile]\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct foo *f;
	struct sockaddr_un sun;
	struct sigaction sa;
	char *sockfile = "/tmp/cool.sock";
	int sfd;
	int backlog = 10;
	char ch;

	argv0 = *argv;
	if ((ch = getopt(argc, argv, "b:s:")) != -1) {
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
	/* FIXME*/
	/*if (sigaction(SIGHUP, &sa, NULL) < 0)*/
		/*err(1, "sigaction: SIGHUP");*/
	/*if (sigaction(SIGINT, &sa, NULL) < 0)*/
		/*err(1, "sigaction: SIGINT");*/
	/*if (sigaction(SIGTERM, &sa, NULL) < 0)*/
		/*err(1, "sigaction: SIGTERM");*/

	if ((sfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		err(1, "socket");
	(void)memset(&sun, 0, sizeof(sun));
	sun.sun_family = AF_UNIX;
	(void)strncpy(sun.sun_path, sockfile, sizeof(sun.sun_path) - 1);

	if (bind(sfd, (struct sockaddr *)&sun, sizeof(sun)) < 0)
		err(1, "bind");
	if (listen(sfd, backlog) < 0)
		err(1, "listen");

	f = emalloc(sizeof(struct foo));
	f->nsucc = 0;
	f->ntotal = 0;

	for (;;) {
		/* FIXME: blocked by accept(2) */
		if (f_quit)
			break;
		/*
		 * accept(2)'s `addr` and `addrlen` arguments can be NULL if
		 * we don't care about the address information of the client.
		 */
		if ((f->cfd = accept(sfd, NULL, NULL)) < 0)
			continue;
		printf("[%s] accepted client: %d\n", argv0, f->cfd);
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
	free(f);
	/*
	 * bind(2)'s man page states that the socket should be deleted when
	 * it's no longer needed, otherwise it'll stay there even after
	 * we exit.
	 */
	(void)unlink(sockfile);

	return 0;
}
