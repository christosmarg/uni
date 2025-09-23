#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

static int
safe_input(const char *fmt, ...)
{
	va_list args;
	char buf[48];
	int n, rc;

	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	do {
		printf("\r%s", buf);
		rc = scanf("%d", &n);
		(void)getchar();
	} while (rc != 1);

	return (n);
}

static void *
emalloc(size_t nb)
{
	void *p;

	if ((p = malloc(nb)) == NULL)
		err(1, "malloc");

	return (p);
}

static int
strictly_diagonal_dominant(int **a, int n)
{
	int i, j, sum, flag = 1;

#pragma omp parallel for
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j)
				continue;
			sum += abs(a[i][j]);
		}
		if (abs(a[i][i]) <= sum)
			flag = 0;
	}

	return (flag);
}

static int
diagonal_max(int **a, int n)
{
	int i, max;

	max = a[0][0];
#pragma omp parallel for reduction(max : max)
	for (i = 0; i < n; i++) {
		if (abs(a[i][i]) > max)
			max = a[i][i];
	}

	return (max);
}

static int **
new_array(int **a, int m, int n)
{
	int **b, i, j;

	b = emalloc(n * sizeof(int *));
#pragma omp parallel for
	for (i = 0; i < n; i++) {
		b[i] = emalloc(n * sizeof(int));
		for (j = 0; j < n; j++)
			b[i][j] = m - a[i][j];
	}

	return (b);
}

static int
min_reduction(int **b, int n)
{
	int i, min;

	min = b[0][0];
#pragma omp parallel for reduction(min : min)
	for (i = 0; i < n; i++) {
		if (b[i][i] < min)
			min = b[i][i];
	}

	return (min);
}

/* TODO: min_no_reduction() */

int
main(int argc, char *argv[])
{
	int **a, **b;
	int i, j, m, min, n, ntd;

	ntd = safe_input("threads: ", 0);
	omp_set_num_threads(ntd);

	n = safe_input("n: ", 0);
	a = emalloc(n * sizeof(int *));
	for (i = 0; i < n; i++) {
		a[i] = emalloc(n * sizeof(int));
		for (j = 0; j < n; j++)
			a[i][j] = safe_input("a[%d][%d]: ", i, j);
	}

	if (strictly_diagonal_dominant(a, n)) {
		m = diagonal_max(a, n);
		printf("diagonal_max: %d\n", m);

		b = new_array(a, m, n);

		min = min_reduction(b, n);
		printf("min_reduction: %d\n", min);

		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				printf("b[%d][%d]: %d\n", i, j, b[i][j]);
		free(b);
	} else
		printf("not strictly diagonal dominant\n");

	free(a);

	return (0);
}
