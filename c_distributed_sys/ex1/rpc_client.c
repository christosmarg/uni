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

#include "rpc.h"

static void	serve_client(char *, int);
static void	sighandler(int);
static void	*emalloc(size_t);
static void	usage(void);

static char	*argv0;
/* becomes true when a termination signal is caught */
static volatile sig_atomic_t f_quit = 0;

void
calc_avg_prog_1(char *host, int sock)
{
	CLIENT *clnt;
	float  *result_1;
	arg_arr  calc_avg_1_arg;
	int *np, *arrp;

#ifndef	DEBUG
	clnt = clnt_create(host, calc_avg_PROG, calc_avg_VERS, "netpath");
	if (clnt == (CLIENT *) NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}
#endif	/* DEBUG */
	
	/* avoid typing all this */
	np = &calc_avg_1_arg.n;

	/* receive number of elements */
	if (recv(sock, np, sizeof(int), 0) < 0)
		goto fail;
	calc_avg_1_arg.arr.arr_len = *np;
	calc_avg_1_arg.arr.arr_val = emalloc(*np * sizeof(int));
	arrp = calc_avg_1_arg.arr.arr_val;

	/* receive array */
	if (recv(sock, arrp, *np * sizeof(int), 0) < 0)
		goto fail;

	/* make RPC */
	result_1 = calc_avg_1(&calc_avg_1_arg, clnt);
	if (result_1 == (float *) NULL) {
		clnt_perror(clnt, "call failed");
	}

	/* send results back to sock_client */
	printf("[%s] sock: %d\tserver response: avg: %.3f\n", argv0, sock, *result_1);
	if (send(sock, result_1, sizeof(float), 0) < 0)
		goto fail;
	return;
fail:
	/* we failed... */
	fprintf(stderr, "[%s] connection with client %d dropped\n", argv0, sock);
	close(sock);
	if (arrp != NULL)
		free(arrp);
#ifndef	DEBUG
	clnt_destroy(clnt);
#endif		/* DEBUG */
}


void
calc_minmax_prog_1(char *host, int sock)
{
	CLIENT *clnt;
	struct minmax  *result_1;
	arg_arr  calc_minmax_1_arg;
	int i, *np, *arrp;

#ifndef	DEBUG
	clnt = clnt_create(host, calc_minmax_PROG, calc_minmax_VERS, "netpath");
	if (clnt == (CLIENT *) NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}
#endif	/* DEBUG */

	np = &calc_minmax_1_arg.n;

	if (recv(sock, np, sizeof(int), 0) < 0)
		goto fail;
	calc_minmax_1_arg.arr.arr_len = *np;
	calc_minmax_1_arg.arr.arr_val = emalloc(*np * sizeof(int));
	arrp = calc_minmax_1_arg.arr.arr_val;

	if (recv(sock, arrp, *np * sizeof(int), 0) < 0)
		goto fail;

	result_1 = calc_minmax_1(&calc_minmax_1_arg, clnt);
	if (result_1 == (struct minmax *) NULL) {
		clnt_perror(clnt, "call failed");
	}

	printf("[%s] server response: min: %d\tmax: %d\n",
	    argv0, result_1->arr.arr_val[0], result_1->arr.arr_val[1]);
	if (send(sock, result_1->arr.arr_val, 2 * sizeof(int), 0) < 0)
		goto fail;
	return;
fail:
	fprintf(stderr, "[%s] connection with client %d dropped\n", argv0, sock);
	close(sock);
	if (arrp != NULL)
		free(arrp);
#ifndef	DEBUG
	clnt_destroy(clnt);
#endif		/* DEBUG */
}


void
calc_prod_prog_1(char *host, int sock)
{
	CLIENT *clnt;
	struct float_arr  *result_1;
	arg_prod  calc_prod_1_arg;
	int i, *np, *arrp;
	float *ap;

#ifndef	DEBUG
	clnt = clnt_create(host, calc_prod_PROG, calc_prod_VERS, "netpath");
	if (clnt == (CLIENT *) NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}
#endif	/* DEBUG */

	ap = &calc_prod_1_arg.a;
	np = &calc_prod_1_arg.arr.n;

	if (recv(sock, ap, sizeof(float), 0) < 0)
		goto fail;
	if (recv(sock, np, sizeof(int), 0) < 0)
		goto fail;
	calc_prod_1_arg.arr.arr.arr_len = *np;
	calc_prod_1_arg.arr.arr.arr_val = emalloc(*np * sizeof(int));
	arrp = calc_prod_1_arg.arr.arr.arr_val;

	if (recv(sock, arrp, *np * sizeof(int), 0) < 0)
		goto fail;

	result_1 = calc_prod_1(&calc_prod_1_arg, clnt);
	if (result_1 == (struct float_arr *) NULL) {
		clnt_perror(clnt, "call failed");
	}

	printf("[%s] server response: [", argv0);
	for (i = 0; i < calc_prod_1_arg.arr.n; i++) {
		printf("%.3f%s", result_1->arr.arr_val[i],
		    i == calc_prod_1_arg.arr.n - 1 ? "" : ", ");
	}
	printf("]\n");

	if (send(sock, result_1->arr.arr_val, *np * sizeof(float), 0) < 0)
		goto fail;
	return;
fail:
	/* we failed... */
	fprintf(stderr, "[%s] connection with client %d dropped\n", argv0, sock);
	close(sock);
	if (arrp != NULL)
		free(arrp);
#ifndef	DEBUG
	clnt_destroy(clnt);
#endif		/* DEBUG */
}

static void
serve_client(char *host, int cfd)
{
	int n;

	for (;;) {
		/* receive option */
		if (recv(cfd, &n, sizeof(int), 0) < 0) {
			fprintf(stderr, "[%s] connection with %d dropped\n",
			    argv0, cfd);
			close(cfd);
			_exit(0);
		}
		switch (n) {
		case 1:
			calc_avg_prog_1(host, cfd);
			break;
		case 2:
			calc_minmax_prog_1(host, cfd);
			break;
		case 3:
			calc_prod_prog_1(host, cfd);
			break;
		case 4:
			printf("[%s] sock %d disconnected\n", argv0, cfd);
			close(cfd);
			return;
		}
	}
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
	return (p);
}

static void
usage(void)
{
	fprintf(stderr, "usage: %s [-p port] hostname\n", argv0);
	exit(0);
}

int
main(int argc, char *argv[])
{
	struct sockaddr_in sin;
	struct hostent *hp;
	struct sigaction sa;
	int backlog = 5;
	int port = 9999;
	int sfd, cfd;
	char *host, ch;

	argv0 = *argv;
	while ((ch = getopt(argc, argv, "b:p:")) != -1) {
		switch (ch) {
		case 'b':
			if ((backlog = atoi(optarg)) < 1)
				errx(1, "backlog value must be > 1");
			break;
		case 'p':
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

	if (argc < 1)
		usage();
	host = *argv;

	memset(&sa, 0, sizeof(sa));
	sigfillset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	/* be sensitive to termination signals */
	if (sigaction(SIGINT, &sa, NULL) < 0)
		err(1, "sigaction(SIGINT)");
	if (sigaction(SIGTERM, &sa, NULL) < 0)
		err(1, "sigaction(SIGTERM)");

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err(1, "socket(AF_INET)");
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(sfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(1, "connect");
	if (listen(sfd, backlog) < 0)
		err(1, "listen");

	for (;;) {
		if (f_quit)
			break;

		if ((cfd = accept(sfd, NULL, NULL)) < 0)
			continue;
		printf("[%s] accepted client at sock: %d\n", argv0, cfd);

		switch (fork()) {
		case -1:
			err(1, "fork");
		case 0:
			serve_client(host, cfd);
			_exit(0);
		default:
			close(cfd);
		}

	}
	close(sfd);

	return (0);
}
