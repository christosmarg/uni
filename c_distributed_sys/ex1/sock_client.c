#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	esend(int, void *, size_t, int);
static void	erecv(int, void *, size_t, int);
static void	*emalloc(size_t);
static void	safe_scanf(void *, char *, char *, ...);
static void	calc_avg(int);
static void	calc_minmax(int);
static void	calc_prod(int);
static void	usage(void);

static char	*argv0;

static void
esend(int fd, void *msg, size_t len, int flags)
{
	if (send(fd, msg, len, flags) < 0)
		err(1, "send");
}

static void
erecv(int fd, void *msg, size_t len, int flags)
{
	if (recv(fd, msg, len, flags) < 0)
		err(1, "recv");
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
safe_scanf(void *n, char *type, char *fmt, ...)
{
	va_list ap;
	char buf[BUFSIZ];
	int rc;

	do {
		va_start(ap, fmt);
		vsprintf(buf, fmt, ap);
		va_end(ap);
		printf("\r%s", buf);
		rc = scanf(type, n);
		(void)getchar();
	} while (rc != 1);
}

static void
calc_avg(int fd)
{
	float res;
	int *arr, n, i;

	safe_scanf(&n, "%d", "%s> n: ", argv0);
	arr = emalloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		safe_scanf(&arr[i], "%d", "%s> arr[%d]: ", argv0, i);

	esend(fd, &n, sizeof(int), 0);
	esend(fd, arr, n * sizeof(int), 0);
	
	erecv(fd, &res, sizeof(float), 0);
	printf("[%s] server response: %.3f\n", argv0, res);

	free(arr);
}

static void
calc_minmax(int fd)
{
	int res[2], *arr, n, i;

	safe_scanf(&n, "%d", "%s> n: ", argv0);
	arr = emalloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		safe_scanf(&arr[i], "%d", "%s> arr[%d]: ", argv0, i);

	esend(fd, &n, sizeof(int), 0);
	esend(fd, arr, n * sizeof(int), 0);

	erecv(fd, &res, 2 * sizeof(int), 0);
	printf("[%s] server response: min: %d\tmax: %d\n",
	    argv0, res[0], res[1]);

	free(arr);
}

static void
calc_prod(int fd)
{
	float *res, a;
	int *arr, n, i;

	safe_scanf(&a, "%f", "%s> a: ", argv0);
	safe_scanf(&n, "%d", "%s> n: ", argv0);
	arr = emalloc(n * sizeof(int));
	for (i = 0; i < n; i++)
		safe_scanf(&arr[i], "%d", "%s> arr[%d]: ", argv0, i);

	esend(fd, &a, sizeof(float), 0);
	esend(fd, &n, sizeof(int), 0);
	esend(fd, arr, n * sizeof(int), 0);

	res = emalloc(n * sizeof(float));
	erecv(fd, res, n * sizeof(float), 0);
	printf("[%s] server response: [", argv0);
	for (i = 0; i < n; i++)
		printf("%.3f%s", res[i], i == n - 1 ? "" : ", ");
	printf("]\n");

	free(arr);
	free(res);
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
	int port = 9999;
	int fd, n;
	char *host, ch;

	argv0 = *argv;
	while ((ch = getopt(argc, argv, "p:")) != -1) {
		switch (ch) {
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

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err(1, "socket(AF_INET)");
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (!inet_aton(host, &sin.sin_addr)) {
		if ((hp = gethostbyname(host)) == NULL)
			errx(1, "gethostbyname(%s) failed", host);
		(void)memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
	}
	if (connect(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(1, "connect");

	for (;;) {
		printf("1: average\n2: min and max\n3: product\n4: disconnect\n");
		safe_scanf(&n, "%d", "%s> your choice: ", argv0);

		switch (n) {
		case 1:
			esend(fd, &n, sizeof(int), 0);
			calc_avg(fd);
			break;
		case 2:
			esend(fd, &n, sizeof(int), 0);
			calc_minmax(fd);
			break;
		case 3:
			esend(fd, &n, sizeof(int), 0);
			calc_prod(fd);
			break;
		case 4:
			esend(fd, &n, sizeof(int), 0);
			goto end;
		default:
			printf("[%s] invalid choice\n", argv0);
		}
	}
end:
	close(fd);

	return (0);
}
