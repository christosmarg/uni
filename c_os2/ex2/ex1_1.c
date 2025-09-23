#include <err.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LEN(x) (sizeof(x) / sizeof(x[0]))

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 1.1 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex1_1.c -lpthread -o ex1_1`
 */

struct foo {
	char *str;
	sem_t sem;
};

/* Function declarations */
static void *tdprint(void *);
static void *emalloc(size_t);
static void usage(void);

/* Global variables */
static char *argv0;
/* 
 * Each thread will print one of these. Everything will adapt in case more
 * strings are added to the array. 
 */
static const char *nums[] = {
	"<one>",
	"<two>",
	"<three>",
};

static void *
tdprint(void *foo)
{
	struct foo *f;
	
	f = (struct foo *)foo;
	if (sem_wait(&f->sem) < 0)
		err(1, "sem_wait");
	printf("%s", f->str);
	/* Prevent memory leak from strdup(2). */
	free(f->str);
	if (sem_post(&f->sem) < 0)
		err(1, "sem_post");

	return NULL;
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
	fprintf(stderr, "usage: %s [-n times]\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct foo *f;
	pthread_t *tds;
	int i, len, n = 5;
	char ch;

	argv0 = *argv;
	while ((ch = getopt(argc, argv, "n:")) != -1) {
		switch (ch) {
		case 'n':
			if ((n = atoi(optarg)) < 1)
				usage();
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	
	len = LEN(nums);
	/*
	 * Instead of hardcoding how many threads we want to have, the
	 * number of threads is always equal to how many elements the
	 * `nums` array has. That means in case we want to add/remove
	 * entries from `nums`, everything will adapt automatically.
	 */
	tds = emalloc(len * sizeof(pthread_t));
	f = emalloc(sizeof(struct foo));

	if (sem_init(&f->sem, 0, 1) < 0)
		err(1, "sem_init");
	while (n--) {
		for (i = 0; i < len; i++) {
			if ((f->str = strdup(nums[i])) == NULL)
				err(1, "strdup");
			if (pthread_create(&tds[i], NULL, tdprint, (void *)f) != 0)
				err(1, "pthread_create");
			if (pthread_join(tds[i], NULL) != 0)
				err(1, "pthread_join");
		}
	}
	printf("\n");

	(void)sem_destroy(&f->sem);
	pthread_exit(NULL);
	free(tds);
	free(f);

	return 0;
}
