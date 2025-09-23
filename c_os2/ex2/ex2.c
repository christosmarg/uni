#include <err.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 2: Άσκηση 2 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex2.c -lpthread -DLLIM=x -DULIM=y -o ex2`
 *	Όπου `x` και `y` το κάτω και πάνω όριο αντίστοιχα.
 */

struct foo {
	int **g_arr;	/* Global array. */
	int **d;	/* `d[i][j] = g_max - g_arr[i][j]` */
	int *l_max;	/* Local maximums. */
	int g_max;	/* Global maximum. */
	int l_n;	/* Number of elements each thread will work with. */
	int n;		/* Dimensions. */
	int ntd;	/* Number of threads. */
	int tid;	/* Thread ID. */
	pthread_mutex_t mtx;
	pthread_barrier_t bar;
};

static void *threaded_stuff(void *);
static void *emalloc(size_t);
static void usage(void);

static char *argv0;

static void *
thread_callback(void *foo)
{
	struct foo *f;
	int i, j, start, end, max, rc;
	
	f = (struct foo *)foo;
	/* 
	 * Each thread reads X rows from `g_arr`. Suppose that we have
	 * 2 threads and a 4x4 array:
	 *	
	 * row: 0 |  1,  2,  3,  4 |
	 * row: 1 |  5,  6,  7,  8 |
	 * row: 2 |  9, 10, 11, 12 |
	 * row: 3 | 13, 14, 15, 16 |
	 *
	 * Each thread now has to work with 2 rows from the array since
	 * `l_n = n / p = 4 / 2 = 2`. But in order to get the
	 * correct row, we have to offset it by the thread number.
	 *
	 * So, thread 0 will read the following part of `g_arr`:
	 *	start: tid * l_n -> 0 * 2 -> 0
	 *	end: start + l_n -> 0 + 2 -> 2
	 *
	 * which is the first half of `g_arr`:
	 *	row: 0 | 1, 2, 3, 4 |
	 *	row: 1 | 5, 6, 7, 8 |
	 *
	 * Following the same logic, thread 1 will read at:
	 *	start = 1 * 2 -> 2
	 *	end = 2 + 2 -> 4
	 *
	 * which is the second half of `g_arr`:
	 *	row: 2 |  9, 10, 11, 12 |
	 *	row: 3 | 13, 14, 15, 16 |
	 *
	 */
	start = f->tid * f->l_n;
	end = start + f->l_n;

	/* Calculate the local max. */
	max = *f->g_arr[start];
	for (i = start; i < end; i++)
		for (j = 0; j < f->n; j++)
			if (f->g_arr[i][j] > max)
				max = f->g_arr[i][j];
	f->l_max[f->tid] = max;

	/* Calculate the global max right away, no need for more functions. */
	if (pthread_mutex_lock(&f->mtx) != 0)
		err(1, "pthread_mutex_lock");
	if (f->tid == 0)
		f->g_max = *f->l_max;
	else if (f->l_max[f->tid] > f->g_max)
		f->g_max = f->l_max[f->tid];

	/* 
	 * We need to know each thread's ID in order to calculate `start`
	 * and `end` properly. Since we don't touch `f->tid` inside `main`
	 * (apart from initializing it), we need to update it here.
	 */
	f->tid++;
	if (pthread_mutex_unlock(&f->mtx) != 0)
		err(1, "pthread_mutex_unlock");

	/* 
	 * Wait for all threads to finish executing the statements above, 
	 * then continue. 
	 */
	rc = pthread_barrier_wait(&f->bar);
	if ((rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) || errno == EINVAL)
		err(1, "pthread_barrier_wait");

	/* 
	 * We'll get here once all threads have passed the barrier, which
	 * means that `f->tid` will be equal to the total number of threads.
	 * In order for `start` and `end` to be offset properly again, we now 
	 * need to go backwards.
	 */
	if (pthread_mutex_lock(&f->mtx) != 0)
		err(1, "pthread_mutex_lock");
	f->tid--;
	if (pthread_mutex_unlock(&f->mtx) != 0)
		err(1, "pthread_mutex_unlock");

	/* Calculate the D array. */
	start = f->tid * f->l_n;
	end = start + f->l_n;
	for (i = start; i < end; i++)
		for (j = 0; j < f->n; j++)
			f->d[i][j] = f->g_max - f->g_arr[i][j];

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
	fprintf(stderr, "usage: %s [-t threads]\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct foo *f;
	pthread_t *tds;
	int i, j, rc;

	argv0 = *argv;
	f = emalloc(sizeof(struct foo));

	do {
		printf("\rp: ");
		/* 
		 * Save the return value of scanf(3) to make sure
		 * we did read valid input.
		 */
		rc = scanf("%d", &f->ntd);
		/* Flush input buffer. */
		(void)getchar();
	/* Cannot have less than 1 threads. */
	} while (f->ntd < 1 || rc != 1);

	do {
		printf("\rn: ");
		rc = scanf("%d", &f->n);
		(void)getchar();
	/* 
	 * The number of elements must be greater than 0 (obviously) and
	 * a multiple of the total number of threads.
	 */
	} while (f->n < 0 || f->n % f->ntd != 0 || rc != 1);

	tds = emalloc(f->ntd * sizeof(pthread_t));
	f->l_n = f->n / f->ntd;
	f->g_arr = emalloc(f->n * sizeof(int *));
	f->l_max = emalloc(f->ntd * sizeof(int));
	f->d = emalloc(f->n * sizeof(int *));
	
	/* The exercise says we should read from a file, but don't do it. :-) */
	srand(time(NULL));
	for (i = 0; i < f->n; i++) {
		f->g_arr[i] = emalloc(f->n * sizeof(int));
		f->d[i] = emalloc(f->n * sizeof(int));
		for (j = 0; j < f->n; j++)
			f->g_arr[i][j] = rand() % (ULIM - LLIM) + LLIM;
	}

	if (pthread_mutex_init(&f->mtx, NULL) != 0)
		err(1, "pthread_mutex_init");
	if (pthread_barrier_init(&f->bar, NULL, f->ntd) != 0)
		err(1, "pthread_barrier_init");

	for (i = 0, f->tid = 0; i < f->ntd; i++)
		if (pthread_create(&tds[i], NULL, thread_callback, (void *)f) != 0)
			err(1, "pthread_create");
	for (i = 0; i < f->ntd; i++)
		if (pthread_join(tds[i], NULL) != 0)
			err(1, "pthread_join");

	/* Print results. */
	for (i = 0; i < f->n; i++)
		for (j = 0; j < f->n; j++)
			printf("arr[%d][%d]: %d\td[%d][%d]: %d\n",
			    i, j, f->g_arr[i][j],
			    i, j, f->d[i][j]);
	printf("max: %d\n", f->g_max);

	(void)pthread_barrier_destroy(&f->bar);
	(void)pthread_mutex_destroy(&f->mtx);
	pthread_exit(NULL);
	free(tds);
	while (f->n--) {
		free(*f->g_arr++);
		free(*f->d++);
	}
	free(f->g_arr);
	free(f->l_max);
	free(f->d);
	free(f);

	return 0;
}
