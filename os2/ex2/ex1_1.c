#include <err.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 1.1 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex1_1.c -lpthread -lrt -o ex1_1`
 */

/* Calculate an array's length. */
#define LEN(x) (sizeof(x) / sizeof(x[0]))

struct foo {
	char *str;
	int tid;
	sem_t sem;
};

/* Function declarations */
static void *thread_callback(void *);
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
thread_callback(void *foo)
{
	struct foo *f;
	
	f = (struct foo *)foo;
	/* Lock the semaphore (decrement by one). */
	if (sem_wait(&f->sem) < 0)
		err(1, "sem_wait");
	/* 
	 * Get appropriate string. `f->tid` has the thread's ID -- we'll use
	 * it to give each thread a unique string. Thread 0 will get the first
	 * string, thread 1 the second, and so on.
	 */
	if ((f->str = strdup(nums[f->tid++])) == NULL)
		err(1, "strdup");
	fputs(f->str, stdout);
	free(f->str);
	/* Unlock the semaphore (increment by one). */
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
			/* 
			 * Manually choose how many times the string sequence
			 * is going to be printed. Obviously, we cannot allow
			 * an N less than 1. By default `n` is 5 (see 
			 * declaration above).
			 */
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
	/*
	 * Instead of hardcoding how many threads we want to have, the
	 * number of threads is always equal to how many elements the
	 * `nums` array has. That means in case we want to add/remove
	 * entries from `nums`, everything will adapt automatically.
	 */
	tds = emalloc(len * sizeof(pthread_t));
	f = emalloc(sizeof(struct foo));

	/* 
	 * sem_init(3)'s second argument defines whether the semaphore
	 * should be shared by multiple processes or not. This is done
	 * by passing a non-zero value, but in this case we want the
	 * semaphore to be shared only by this process.
	 */
	if (sem_init(&f->sem, 0, 1) < 0)
		err(1, "sem_init");

	while (n--) {
		f->tid = 0;
		for (i = 0; i < len; i++)
			if (pthread_create(&tds[i], NULL,
			    thread_callback, (void *)f) != 0)
				err(1, "pthread_create");
		for (i = 0; i < len; i++)
			if (pthread_join(tds[i], NULL) != 0)
				err(1, "pthread_join");
	}
	printf("\n");

	(void)sem_destroy(&f->sem);
	pthread_exit(NULL);
	free(tds);
	free(f);

	return 0;
}
