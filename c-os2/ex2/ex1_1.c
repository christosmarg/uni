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
 * Τρόπος μεταγλώττισης: `cc ex1_1.c -lpthread -o ex1_1`
 */

struct foo {
	char *str;
	sem_t mutex;
};

/* Function declarations */
static void *tdprint(void *);
static void *emalloc(size_t);
static void die(const char *);

/* Global variables */
static char *argv0;
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
	if (sem_wait(&f->mutex) < 0)
		die("sem_wait");
	printf("%s", f->str);
	/* Prevent memory leak from strdup(2). */
	free(f->str);
	if (sem_post(&f->mutex) < 0)
		die("sem_post");

	return NULL;
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
	fprintf(stderr, "%s: ", argv0);
	perror(str);
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct foo *f;
	pthread_t *tds;
	int i, len, n = 5;

	argv0 = *argv;
	len = LEN(nums);
	f = emalloc(sizeof(struct foo));
	/*
	 * Instead of hardcoding how many threads we want to have, the
	 * number of threads is always equal to how many elements the
	 * `nums` array has. That means in case we want to add/remove
	 * entries from `nums`, everything will adapt automatically.
	 */
	tds = emalloc(len * sizeof(pthread_t));

	if (sem_init(&f->mutex, 0, 1) < 0)
		die("sem_init");
	while (n--) {
		for (i = 0; i < len; i++) {
			if ((f->str = strdup(nums[i])) == NULL)
				die("strdup");
			if (pthread_create(&tds[i], NULL, tdprint, (void *)f) != 0)
				die("pthread_create");
			if (pthread_join(tds[i], NULL) != 0)
				die("pthread_join");
		}
	}
	printf("\n");

	(void)sem_destroy(&f->mutex);
	pthread_exit(NULL);
	free(tds);
	free(f);

	return 0;
}
