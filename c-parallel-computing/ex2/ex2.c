#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

static float     input(const char *, int);
static void      readvec(float *, int);
static float     calcavg(float *, int);
static void     *emalloc(size_t);

static float
input(const char *fmt, int i)
{
        char buf[48];
        float n;

        sprintf(buf, fmt, i);
        printf("%s", buf);
        scanf("%f", &n);
        getchar();
        return n;
}

static void
readvec(float *vec, int n)
{
        int i = 0;

        for (; i < n; i++)
                vec[i] = input("vec[%d]: ", i);
}

static void *
emalloc(size_t nb)
{
        void *p;

        if ((p = malloc(nb)) == NULL) {
                fputs("ex2: cannot allocate memory", stderr);
                exit(EXIT_FAILURE);
        }
        return p;
}

static float
calcavg(float *vec, int n)
{
        float sum = 0.0f;
        int i = 0;

        for (; i < n; i++)
                sum += vec[i];
        return (sum / (float)n);
}

int
main(int argc, char *argv[])
{
        int rank, nproc, root = 0;
        int n, localn;
        float *vec, *localvec;
        float localsum, sum;
        float *avgs, localavg, finalavg;
        float var;
        int i;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == root) {
                n = input("N: ", 0);
                vec = emalloc(n * sizeof(float));
                readvec(vec, n);
        }

        /* part 0 - calc avg */
        MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);
        localn = n / nproc;
        localvec = emalloc(localn * sizeof(float));
        MPI_Scatter(vec, localn, MPI_FLOAT, localvec, localn, MPI_FLOAT, root, MPI_COMM_WORLD);

        avgs = emalloc(nproc * sizeof(float));
        localavg = calcavg(localvec, localn);
        MPI_Gather(&localavg, 1, MPI_FLOAT, avgs, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

        if (rank == root) {
                finalavg = calcavg(avgs, nproc);
        }

        /*MPI_Bcast(&finalavg, 1, MPI_FLOAT, root, MPI_COMM_WORLD);*/
        /*MPI_Scatter(vec, localn, MPI_FLOAT, localvec, localn, MPI_FLOAT, root, MPI_COMM_WORLD);*/

        if (rank == root) {
                printf("avg: %.2f\n", finalavg);
        }

        /* move up? */
        free(vec);
        free(localvec);
        free(avgs);

        MPI_Finalize();

        return 0;
}
