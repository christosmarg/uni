#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>

static void	pretty_print(int *, int, const char *);
static int	cmpfunc(const void *, const void *);
static void	merge(int *, int *, int *, int *, int *);
static void	multisort(int *, int *, int);

/*
 * Print the contents of a 2D array like:
 *
 * array = [x, y, z]
 */
static void
pretty_print(int *arr, int n, const char *name)
{
	int i;

	printf("\n%s = [", name);
	for (i = 0; i < n; i++)
		printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
	printf("]\n");
}

/*
 * Passed to qsort(3).
 */
static int
cmpfunc(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

static void
merge(int *a, int *enda, int *b, int *endb, int *res)
{
	while (a <= enda && b <= endb) {
		if (*a < *b)
			*res++ = *a++;
		else
			*res++ = *b++;
	}
	while (a <= enda)
		*res++ = *a++;
	while (b <= endb)
		*res++ = *b++;
}

static void
multisort(int *arr, int *space, int n)
{
	int quarter, *sta, *spa, *stb, *spb, *stc, *spc, *std, *spd;

	if ((quarter = n / 4) < 4)
		qsort(arr, n, sizeof(int), cmpfunc);
	else {
		/* Split the array into 4 quarters. */
		sta = arr;
		spa = space;
		stb = sta + quarter;
		spb = spa + quarter;
		stc = stb + quarter;
		spc = spb + quarter;
		std = stc + quarter;
		spd = spc + quarter;
#pragma omp task
		multisort(sta, spa, quarter);
#pragma omp task
		multisort(stb, spb, quarter);
#pragma omp task
		multisort(stc, spc, quarter);
#pragma omp task
		multisort(std, spd, n - 3 * quarter);
		/* Wait for the tasks above to finish. */
#pragma omp taskwait
#pragma omp task
		/* Merge A and B into SpaceA */
		merge(sta, sta + quarter - 1, stb, stb + quarter - 1, spa);
#pragma omp task
		/* Merge C and D into SpaceC */
		merge(stc, stc + quarter - 1, std, arr + n - 1, spc);
#pragma omp taskwait
		/* Merge the two resulting couples (SpaceA and SpaceC). */
		merge(spa, spc - 1, spc, space + n - 1, arr);
	}
}

int
main(int argc, char *argv[])
{
	int *a, *space, i, n, ntd;
	double start, end;


	if (argc < 3) {
		fprintf(stderr, "usage: %s nthreads n\n", getprogname());
		return (1);
	}
	if ((ntd = atoi(argv[1])) < 1)
		err(1, "can't use nthreads n < 1");
	if ((n = atoi(argv[2])) < 1)
		err(1, "can't use n < 1");

	srand(time(NULL));
	omp_set_num_threads(ntd);

	if ((a = malloc(n * sizeof(int))) == NULL)
		err(1, "malloc");
	if ((space = malloc(n * sizeof(int))) == NULL)
		err(1, "malloc");
	for (i = 0; i < n; i++)
		a[i] = rand() % 100;

	start = omp_get_wtime();

	pretty_print(a, n, "A_unsorted");
	multisort(a, space, n);
	pretty_print(a, n, "A_multisort");

	end = omp_get_wtime();
	printf("Total time: %f seconds\n", end - start);

	free(a);

	return (0);
}
