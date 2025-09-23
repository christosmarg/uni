#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 3 (client) / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex3_client.c -o ex3_client`
 */

/* Results from server. */
struct pack_res {
	char str[32];
	float avg;
};

static void *emalloc(size_t nb);
static void usage(void);

static char *argv0;

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
	fprintf(stderr, "usage: %1$s [-s sockfile]\n"
	    "       %1$s -i [-p port] [-s sockfile] hostname\n"
	    "       %1$s -i [-p port] [-s sockfile] ipv4_addr\n", argv0);
	exit(1);
}

/* Code shared with `ex3_server` is explained in `ex3_server.c`. */
int
main(int argc, char *argv[])
{
	struct pack_res *res;
	struct sockaddr_un sun;
	struct sockaddr_in sin;
	struct hostent *hp;
	char *sockfile = "/tmp/cool.sock";
	int *arr;
	int fd, i, n, rc;
	int port = 9999;
	int iflag, uflag;
	char ch;

	argv0 = *argv;
	uflag = 1;
	iflag = 0;

	while ((ch = getopt(argc, argv, "ip:s:")) != -1) {
		switch (ch) {
		case 'i':
			iflag = 1;
			uflag = 0;
			break;
		case 'p':
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

	if (iflag && argc < 1)
		usage();

	if (iflag) {
		if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			err(1, "socket(AF_INET)");
		(void)memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(port);
		if (!inet_aton(*argv, &sin.sin_addr)) {
			if ((hp = gethostbyname(*argv)) == NULL)
				errx(1, "gethostbyname(%s) failed", *argv);
			(void)memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
		}
		if (connect(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
			err(1, "connect");
	} else if (uflag) {
		if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
			err(1, "socket(AF_UNIX)");
		(void)memset(&sun, 0, sizeof(sun));
		sun.sun_family = AF_UNIX;
		(void)strncpy(sun.sun_path, sockfile, sizeof(sun.sun_path) - 1);
		
		if (connect(fd, (struct sockaddr *)&sun, sizeof(sun)) < 0)
			err(1, "connect");
	}

	res = emalloc(sizeof(struct pack_res));

	for (;;) {
		/* Remove any previous junk. */
		(void)memset(res, 0, sizeof(struct pack_res));

		/* Make sure we send valid input to the server */
		do {
			printf("\r%s> n: ", argv0);
			rc = scanf("%d", &n);
			/* Flush input buffer */
			(void)getchar();
		} while (rc != 1);
		arr = emalloc(n * sizeof(int));
		for (i = 0; i < n; i++) {
			do {
				printf("\r%s> arr[%d]: ", argv0, i);
				rc = scanf("%d", &arr[i]);
				(void)getchar();
			} while (rc != 1);
		}
		if (send(fd, &n, sizeof(int), 0) < 0)
			err(1, "send");
		if (send(fd, arr, n * sizeof(int), 0) < 0)
			err(1, "send");
		if (recv(fd, res, sizeof(struct pack_res), 0) < 0)
			err(1, "recv");
		free(arr);

		printf("server response: %s\tavg: %.2f\n", res->str, res->avg);
		do
			printf("\r%s> continue (y/n)? ", argv0);
		while ((ch = getchar()) != 'y' && ch != 'n');
		if (send(fd, &ch, 1, 0) < 0)
			err(1, "send");
		if (ch == 'n')
			break;
	}
	free(res);
	(void)close(fd);

	return 0;
}
