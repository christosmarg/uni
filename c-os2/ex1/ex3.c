#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 1: Άσκηση 3 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex3.c -lpthread -DLLIM=x -DULIM=y -o ex3`
 *	Όπου `x` και `y` το κάτω και πάνω όριο αντίστοιχα.
 */

/* No globals allowed :-) */
struct foo {
	int *sums;		/* Sums for each thread */
	int *arr;		/* Global vector */
	int n;			/* `arr`'s length */
	int ntd;		/* Number of threads */
	int tid;		/* Thread ID */
	pthread_mutex_t mutex;	/* Protect critical parts */
};

/* Function declarations */
static void *calc(void *);
static void *emalloc(size_t);
static void die(const char *);

/* Global variable */
static char *argv0; /* Program name */

/* 
 * Each thread calculates the sum of the squares of each element in a specified
 * region in `arr`. That range is determined by the thread's ID (e.g the current
 * thread) and the number of elements that each thread has to compute. Since
 * `arr`'s length is a multiple of `ntd`, we can calculate the number of elements
 * each thread will compute by doing `n / ntd`.
 *
 * For example, `ntd = 2` and `n = 4`, and `arr = [1, 2, 3, 4]`.
 * Each thread will compute `n / ntd = 2` elements.
 *
 * Thread 0 will operate in the region:
 *	`td * (n / ntd) = 0 * 2 = 0` to 
 *	`(td + 1) * (n / ntd) - 1 = (0 + 1) * 2 - 1 = 1`
 *
 * Thread 1 will operate in the region:
 *	`1 * 2 = 2` to `(1 + 1) * 2 - 1 = 3`
 *
 * So effectively, each thread will be assigned to compute an equal amount of
 * elements.
 */
static void *
calc(void *foo)
{
	struct foo *f;
	int localsum;
	int tid, n, i;

	f = (struct foo *)foo;
	tid = f->tid;
	n = f->n / f->ntd;
	f->sums[tid] = 0;
	localsum = 0;

	for (i = tid * n; i < (tid + 1) * n; i++) {
		localsum += f->arr[i] * f->arr[i];
		printf("tid: %d\tarr[%d]: %d\n", tid, i, f->arr[i]);
	}
	/* 
	 * Lock the mutex so that no other thread can write
	 * to f->sums at the same time.
	 */ 
	if (pthread_mutex_lock(&f->mutex) != 0)
		die("pthread_mutex_lock");
	f->sums[tid] = localsum;
	if (pthread_mutex_unlock(&f->mutex) != 0)
		die("pthread_mutex_unlock");

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
	struct foo *f;	/* Each callback will receive this */
	pthread_t *tds; /* Threads */
	pthread_t fin;	/* Will calculate the total sum */
	int totalsum;	/* What its name says */
	int i;		/* Counter */

	argv0 = *argv;
	f = emalloc(sizeof(struct foo));
	/* 
	 * We do error checks for `n` and `ntd` but in case we read from a
	 * file the program might break if the data is wrong (i.e fails the
	 * error checks at least once) since it will keep going further down
	 * into the file. The same doesn't apply for when reading from stdin --
	 * we can just give it a new number until it's correct.
	 */
	do {
		printf("p: ");
		scanf("%d", &f->ntd);
	/* Cannot have < 0 threads. */
	} while (f->ntd < 0);

	do {
		printf("n: ");
		scanf("%d", &f->n);
	/* Make sure `n` is positive and also a multiple of `ntd`. */
	} while (f->n < 0 || f->n % f->ntd != 0);

	tds = emalloc(f->ntd * sizeof(pthread_t));
	f->arr = emalloc(f->n * sizeof(int));
	f->sums = emalloc(f->ntd * sizeof(int));

	/* Fill the vector. */
	srand(time(NULL));
	for (i = 0; i < f->n; i++)
		f->arr[i] = rand() % (ULIM - LLIM) + LLIM;

	if (pthread_mutex_init(&f->mutex, NULL) != 0)
		die("pthread_mutex_init");
	/* 
	 * Start multithreading. For each thread we assign `calc`
	 * to be the callback function that each thread will call
	 * and we pass it the `foo` struct as an argument to avoid
	 * declaring globals.
	 */
	for (i = 0; i < f->ntd; i++) {
		f->tid = i;
		if (pthread_create(&tds[i], NULL, calc, (void *)f) != 0)
			die("pthread_create");
		if (pthread_join(tds[i], NULL) != 0)
			die("pthread_join");
	}
	totalsum = 0;
	while (f->ntd--)
		totalsum += *f->sums++;
	printf("total sum: %d\n", totalsum);

	(void)pthread_mutex_destroy(&f->mutex);
	pthread_exit(NULL);
	free(tds);
	free(f->arr);
	free(f->sums);
	free(f);

	return 0;
}
