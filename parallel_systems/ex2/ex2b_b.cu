#include <stdio.h>
#include <time.h>

#define N	(1 << 3)
#define M	(1 << 3)
#define DIM	(N * M)
#define BLKSIZE	(1 << 10)
#define NBLK	((DIM + BLKSIZE - 1) / BLKSIZE)

/*
 * Calculations taken from lab's example code.
 */
__global__ void
transnorm(float *a, float *atrans, float *x, float *y)
{
	int i, j, idx, stridex;

	/* Each thread gets a slice of the rows to work with */
	idx = blockIdx.x * blockDim.x + threadIdx.x;
	stridex = blockDim.x * gridDim.x;

	if (idx >= N)
		return;
	/* First thread initializes y */
	if (threadIdx.x == 0) {
		for (i = 0; i < M; i++)
			y[i] = 0;
	}
	for (i = idx; i < N; i += stridex) {
		for (j = 0; j < M; j++) {
			/* Transpose A */
			atrans[j * N + i] = a[i * M + j];
			y[j] = atrans[j * M + i] * a[i * M + j] * x[j];
		}
	}
}

static void
pretty_print_1d(float *arr, const char *name, int n)
{
	int i;

	printf("\n%s = [", name);
	for (i = 0; i < n; i++) {
		printf("%.2f%s", arr[i],
		   (i == n - 1) ? "" : ", ");
	}
	printf("]\n");
}

static void
pretty_print_2d(float *arr, const char *name, int w, int h)
{
	int i, j;

	printf("\n%s = [\n", name);
	for (i = 0; i < w; i++) {
		printf("\t[");
		for (j = 0; j < h; j++) {
			printf("%.2f%s", arr[i * h + j],
			   (j == h - 1) ? "]\n" : ", ");
		}
	}
	printf("]\n");
}

int
main(int argc, char *argv[])
{
	float *a, *atrans, *x, *y;
	int i, j;

	srand(time(NULL));

	/*
	 * Use unified memory to avoid having additional device arrays and
	 * memcpying from host to device and vice versa.
	 */
	cudaMallocManaged(&a, DIM * sizeof(float));
	cudaMallocManaged(&atrans, DIM * sizeof(float));
	cudaMallocManaged(&x, M * sizeof(float));
	cudaMallocManaged(&y, M * sizeof(float));

	/* Initialize arrays */
	for (i = 0; i < N; i++) {
		x[i] = (float)(rand() % 100);
		for (j = 0; j < M; j++)
			a[i * M + j] = (float)(rand() % 100);
	}

	transnorm<<<NBLK, BLKSIZE>>>(a, atrans, x, y);
	/* Wait for all devices to finish */
	cudaDeviceSynchronize();

	pretty_print_2d(a, "A", N, M);
	pretty_print_2d(atrans, "A_trans", M, N);
	pretty_print_1d(x, "X", M);
	pretty_print_1d(y, "Y", M);

	cudaFree(a);
	cudaFree(atrans);
	cudaFree(x);
	cudaFree(y);

	return (0);
}
