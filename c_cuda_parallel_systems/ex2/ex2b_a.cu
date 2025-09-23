#include <stdio.h>
#include <time.h>

#define N	(1 << 2)
#define DIM	(N * N)
/*
 * This formula for calculating the number of blocks is mentioned at "out of
 * the blocks" section in:
 *
 * https://developer.nvidia.com/blog/even-easier-introduction-cuda/
 */
#define BLKSIZE	(1 << 8)
#define NBLK	((DIM + BLKSIZE - 1) / BLKSIZE)

__global__ void
convolution(float *a, float *aconv)
{
	float c11, c12, c13, c21, c22, c23, c31, c32, c33;
	int i, j, x, stridex;

	/*
	 * Each thread gets a slice of the rows to work with. Grid-stride idiom
	 * mentioned at section "out of the blocks" in:
	 *
	 * https://developer.nvidia.com/blog/even-easier-introduction-cuda/
	 */
	x = blockIdx.x * blockDim.x + threadIdx.x;
	stridex = blockDim.x * gridDim.x;

	/* Random weight values */
	c11 = +0.2;  c21 = +0.5;  c31 = -0.8;
	c12 = -0.3;  c22 = +0.6;  c32 = -0.9;
	c13 = +0.4;  c23 = +0.7;  c33 = +0.10;
	
	if (x < 1 || x > N - 1)
		return;
	for (i = x; i < N - 1; i += stridex) {
		for (j = 1; j < N - 1; j++) {
			/* Taken from the lab's example code. */
			aconv[i * N + j] = 
			    c11 * a[(i - 1)	* N + (j - 1)] +
			    c12 * a[i		* N + (j - 1)] +
			    c13 * a[(i + 1)	* N + (j - 1)] +
			    c21 * a[(i - 1)	* N + j] +
			    c22 * a[i		* N + j] +
			    c23 * a[(i + 1)	* N + j] +
			    c31 * a[(i - 1)	* N + (j + 1)] +
			    c32 * a[i		* N + (j + 1)] +
			    c33 * a[(i + 1)	* N + (j + 1)];
		}
	}
}

__global__ void
min_diagonal(float *arr, float *min_arr)
{
	int x, stridex, i;

	x = blockIdx.x * blockDim.x + threadIdx.x;
	stridex = blockDim.x * gridDim.x;

	if (x >= N)
		return;
	/* Calculate local minimums */
	min_arr[x] = arr[x * N + x];
	for (i = x; i < N; i += stridex)
		if (arr[i * N + i] < min_arr[x])
			min_arr[x] = arr[i * N + i];
}

static void
pretty_print(float *arr, const char *name)
{
	int i, j;

	printf("\n%s = [\n", name);
	for (i = 0; i < N; i++) {
		printf("\t[");
		for (j = 0; j < N; j++) {
			printf("%.2f%s", arr[i * N + j],
			   (j == N - 1) ? "]\n" : ", ");
		}
	}
	printf("]\n");
}

int
main(int argc, char *argv[])
{
	float *a, *aconv, *min_arr, min;
	int i;

	srand(time(NULL));

	/*
	 * Use unified memory to avoid having additional device arrays and
	 * memcpying from host to device and vice versa.
	 *
	 * https://developer.nvidia.com/blog/unified-memory-cuda-beginners/
	 */
	cudaMallocManaged(&a, DIM * sizeof(float));
	cudaMallocManaged(&aconv, DIM * sizeof(float));
	cudaMallocManaged(&min_arr, DIM * sizeof(float));

	/* Initialize array */
	for (i = 0; i < DIM; i++)
		a[i] = (float)(rand() % 100);

	convolution<<<NBLK, BLKSIZE>>>(a, aconv);
	/* Wait for all devices to finish */
	cudaDeviceSynchronize();

	min_diagonal<<<NBLK, BLKSIZE>>>(aconv, min_arr);
	cudaDeviceSynchronize();

	/*
	 * Find global minimum using the local minimums calculated in
	 * min_diagonal().
	 */
	min = min_arr[0];
	for (i = 0; i < N; i++)
		if (min_arr[i] < min)
			min = min_arr[i];

	pretty_print(a, "A");
	pretty_print(aconv, "A_conv");
	printf("Min_diagonal(A_conv): %.2f\n", min);

	cudaFree(a);
	cudaFree(aconv);
	cudaFree(min_arr);

	return (0);
}
