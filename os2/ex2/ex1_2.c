#include <err.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 1.2 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex1_2.c -lpthread -o ex1_2`
 */

#define LEN(x) (sizeof(x) / sizeof(x[0]))

struct foo {
	char *str;
	int done;
	int tid;
	pthread_mutex_t mtx;
	pthread_cond_t cv;
};

/* Function declarations */
static void *thread_callback(void *);
static void *emalloc(size_t);
static void usage(void);

/* Global variables */
static char *argv0;
static const char *nums[] = {
	"<one>",
	"<two>",
	"<three>",
};

static void *
thread_callback(void *foo)
{
	struct foo *f;
	
	f = (struct foo *)foo;
	if (pthread_mutex_lock(&f->mtx) != 0)
		err(1, "pthread_mutex_lock");
	/* 
	 * Set the flag to zero so that the other threads will be blocked
	 * with `pthread_cond_wait`.
	 */
	f->done = 0;
	if ((f->str = strdup(nums[f->tid++])) == NULL)
		err(1, "strdup");
	printf("%s", f->str);
	free(f->str);
	f->done = 1;

	/* If a thread is not done executing the statements above, wait. */
	if (!f->done) {
		if (pthread_cond_wait(&f->cv, &f->mtx) != 0)
			err(1, "pthread_cond_wait");
	/* We're done, the next threads can do their job now. */
	} else {
		if (pthread_cond_signal(&f->cv) != 0)
			err(1, "pthread_cond_signal");
	}
	if (pthread_mutex_unlock(&f->mtx) != 0)
		err(1, "pthread_mutex_unlock");

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

/* Code shared with `ex1_1` is explained in `ex1_1.c`. */
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
				errx(1, "value must be greater than 1");
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;
	
	len = LEN(nums);
	tds = emalloc(len * sizeof(pthread_t));
	f = emalloc(sizeof(struct foo));

	if (pthread_mutex_init(&f->mtx, NULL) != 0)
		err(1, "pthread_mutex_init");
	if (pthread_cond_init(&f->cv, NULL) != 0)
		err(1, "pthread_cond_init");

	while (n--) {
		f->done = f->tid = 0;
		for (i = 0; i < len; i++)
			if (pthread_create(&tds[i], NULL, 
			    thread_callback, (void *)f) != 0)
				err(1, "pthread_create");
		for (i = 0; i < len; i++)
			if (pthread_join(tds[i], NULL) != 0)
				err(1, "pthread_join");
	}
	printf("\n");

	(void)pthread_mutex_destroy(&f->mtx);
	(void)pthread_cond_destroy(&f->cv);
	pthread_exit(NULL);
	free(tds);
	free(f);

	return 0;
}
