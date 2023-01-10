#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

static int	safe_input(const char *, ...);
static void	pretty_print(int *, int, const char *);

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

int
main(int argc, char *argv[])
{
	int *a, i, n, ntd;
	double start, end;


	ntd = safe_input("threads: ", 0);
	omp_set_num_threads(ntd);

	n = safe_input("n: ", 0);
	if ((a = malloc(n * sizeof(int))) == NULL)
		err(1, "malloc");
	for (i = 0; i < n; i++)
		a[i] = safe_input("a[%d]: ", i);

	start = omp_get_wtime();

	/* TODO */
	<++>

	end = omp_get_wtime();
	printf("Total time: %f seconds\n", end - start);

	pretty_print(a, n, "A_unsorted");
	pretty_print(a, n, "A_multisort");

	free(a);

	return (0);
}
