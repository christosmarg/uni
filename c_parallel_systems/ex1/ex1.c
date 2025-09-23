#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#define abs(x)	((x) < 0 ? -(x) : (x))

static void	*emalloc(size_t);
static int	safe_input(const char *, ...);
static void	pretty_print(int **, int, const char *);
static int	strictly_diagonal_dominant(int **, int);
static int	diagonal_max(int **, int);
static int	**new_array(int **, int, int);
static int	calc_min(int **, int);

/*
 * Fail-safe malloc(3).
 */
static void *
emalloc(size_t nb)
{
	void *p;

	if ((p = malloc(nb)) == NULL)
		err(1, "malloc");

	return (p);
}

static int
safe_input(const char *fmt, ...)
{
	va_list args;
	char buf[48];
	int n, rc;

	/* Collect the arguments into a buffer. */
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	/*
	 * The following loop keeps asking for input as long as the current
	 * input wasn't correct. In this case "incorrect" input means anything
	 * other than digits.
	 */
	do {
		printf("\r%s", buf);
		rc = scanf("%d", &n);
		(void)getchar();
	} while (rc != 1);

	return (n);
}

/*
 * Print the contents of a 2D array like:
 *
 * array = [
 *	[x, y, z]
 *	[x, y, z]
 * ]
 */
static void
pretty_print(int **arr, int n, const char *name)
{
	int i, j;

	printf("\n%s = [\n", name);
	for (i = 0; i < n; i++) {
		printf("\t[");
		for (j = 0; j < n; j++) {
			printf("%d%s", arr[i][j],
			   (j == n - 1) ? "]\n" : ", ");
		}
	}
	printf("]\n");
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
calc_min(int **b, int n)
{
	int i, j, min;

	/* with reduction */
	min = b[0][0];
#pragma omp parallel for reduction(min : min)
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (b[i][j] < min)
				min = b[i][j];
		}
	}

	/* without reduction, with critical region protection */
	min = b[0][0];
#pragma omp parallel for private(i, j) shared(min)
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
#pragma omp critical
		{
			if (b[i][j] < min)
				min = b[i][j];
		}
		}
	}

	/* XXX: didn't implement binary tree method */

	return (min);
}

int
main(int argc, char *argv[])
{
	int **a, **b;
	int i, j, m, min, n, ntd;
	double start, end;

	ntd = safe_input("threads: ", 0);
	omp_set_num_threads(ntd);

	n = safe_input("n: ", 0);
	a = emalloc(n * sizeof(int *));
	for (i = 0; i < n; i++) {
		a[i] = emalloc(n * sizeof(int));
		for (j = 0; j < n; j++)
			a[i][j] = safe_input("a[%d][%d]: ", i, j);
	}

	start = omp_get_wtime();

	if (strictly_diagonal_dominant(a, n)) {
		m = diagonal_max(a, n);
		b = new_array(a, m, n);
		min = calc_min(b, n);

		pretty_print(a, n, "A");
		pretty_print(b, n, "B");
		printf("Diagonal max: %d\n", m);
		printf("Min: %d\n", min);

		free(b);
	} else
		printf("not strictly diagonal dominant\n");

	end = omp_get_wtime();
	printf("Total time: %f seconds\n", end - start);

	free(a);

	return (0);
}
