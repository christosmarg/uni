#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

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

static void *emalloc(size_t);
static void die(const char *);

static char *argv0;

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

int
main(int argc, char *argv[])
{
	struct pack_res *res;
	struct sockaddr_un sun;
	char *sockfile = "/tmp/cool.sock";
	int *arr;
	int fd, i, n;
	char ch;

	argv0 = *argv;
	while ((ch = getopt(argc, argv, "s:")) != -1) {
		switch (ch) {
		case 's':
			sockfile = optarg;
			break;
		case '?':
		default:
			fprintf(stderr, "usage: %s [-s sockfile]\n", argv0);
			break;
		}
	}
	argc -= optind;
	argv += optind;


	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		die("socket");
	(void)memset(&sun, 0, sizeof(sun));
	sun.sun_family = AF_UNIX;
	(void)strncpy(sun.sun_path, sockfile, sizeof(sun.sun_path) - 1);
	if (connect(fd, (struct sockaddr *)&sun, sizeof(struct sockaddr_un)) == -1)
		die("connect");

	res = emalloc(sizeof(struct pack_res));

	for (;;) {

		/* Remove any previous junk. */
		(void)memset(res, 0, sizeof(struct pack_res));

		printf("%s> n: ", argv0);
		scanf("%d", &n);
		/* Flush buffer */
		(void)getchar();
		arr = emalloc(n * sizeof(int));
		for (i = 0; i < n; i++) {
			printf("%s> arr[%d]: ", argv0, i);
			scanf("%d", &arr[i]);
		}
		(void)getchar();
		if (send(fd, &n, sizeof(int), 0) == -1)
			die("send");
		if (send(fd, arr, n * sizeof(int), 0) == -1)
			die("send");
		if (recv(fd, res, sizeof(struct pack_res), 0) == -1)
			die("recv");
		printf("response: %s\tavg: %.2f\n", res->str, res->avg);

		printf("%s> continue (y/n)? ", argv0);
		ch = getchar();
		if (send(fd, &ch, 1, 0) == -1)
			die("send");
		if (ch == 'n')
			break;
	}

	free(res);
	(void)close(fd);

	return 0;
}
