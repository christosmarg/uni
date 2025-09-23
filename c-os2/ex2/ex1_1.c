#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN(x) (sizeof(x) / sizeof(x[0]))

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 1.1 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex1_1.c -lpthread -lrt -o ex1_1`
 */

struct foo {
	sem_t mutex;
	char *str;
};

/* Function declarations */
static void *tdprint(void *);
static void *emalloc(size_t);
static void die(const char *);

/* Global variables */
static char *argv0; 		/* Program name */
static const char *nums[] = {	/* Each thread will print one of these */
	"<one>",
	"<two>",
	"<three>",
};

static void *
tdprint(void *foo)
{
	struct foo *f;
	
	f = (struct foo *)foo;
	sem_wait(&f->mutex);
	printf("%s", f->str);
	/* Prevent memory leak from strdup(2). */
	free(f->str);
	sem_post(&f->mutex);

	return NULL;
}

/* Error checking malloc(2) */
static void *
emalloc(size_t nb)
{
	void *p;

	if ((p = malloc(nb)) == NULL)
		die("malloc");
	return p;
}

/* Die. */
static void
die(const char *str)
{
	fprintf(stderr, "%s: ", argv0);
	perror(str);
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	struct foo *f;
	pthread_t *tds;
	int len;
	int n = 5;
	int i;

	argv0 = *argv;
	len = LEN(nums);
	f = emalloc(sizeof(struct foo));
	tds = emalloc(len * sizeof(pthread_t));

	sem_init(&f->mutex, 0, 1);
	while (n--) {
		for (i = 0; i < len; i++) {
			/* Get appropriate string. */
			f->str = strdup(nums[i % len]);
			if (pthread_create(&tds[i], NULL, tdprint, (void *)f) != 0)
				die("pthread_create");
			if (pthread_join(tds[i], NULL) != 0)
				die("pthread_join");
		}
	}
	printf("\n");

	sem_destroy(&f->mutex);
	pthread_exit(NULL);
	free(tds);
	free(f);

	return 0;
}
