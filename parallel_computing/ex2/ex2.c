#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/* Flags */
#define FIND_XMIN       1 << 0
#define FIND_XMAX       1 << 1
#define COUNT_BELOW_AVG 1 << 2
#define COUNT_ABOVE_AVG 1 << 3

typedef struct {
        float val;      /* Max value in array */
        int i;          /* Index of max */
} Pair;

/* Function declarations */
static float     input(const char *, int);
static float     find(int);
static float     findavg(float *, int);
static float     calcavg(void);
static int       count(float, int);
static float     calcvar(float);
static float    *calcd(float, float);
static Pair      findmax(float *);
static float    *calcpfxsums(void);
static void      printv(const char *, const float *);
static void     *emalloc(size_t);

/* Global variables */
static int rank, nproc, root = 0;
static int *scounts, *displs;
static float *vec, *localvec;
static int n, localn;

/* Function implementations */
/* Formatted input */
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

/* Find `xmin` and `xmax` depending on the `flag` argument. */
static float
find(int flag)
{
        float localres = *localvec;
        float finalres = localres;
        float *res;
        int i;

        res = emalloc(nproc * sizeof(float));
        /*
         * Loop through each local vector and assign the local
         * result depending on which of the two flags is set 
         */
        for (i = 0; i < localn; i++)
                if ((flag & FIND_XMIN && localvec[i] < localres)
                ||  (flag & FIND_XMAX && localvec[i] > localres))
                        localres = localvec[i];
        /* Send local results to `root` */
        MPI_Gather(&localres, 1, MPI_FLOAT, res, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

        if (rank == root)
                /* Same process as above */
                for (i = 0; i < nproc; i++)
                        if ((flag & FIND_XMIN && res[i] < finalres)
                        ||  (flag & FIND_XMAX && res[i] > finalres))
                                finalres = res[i];

        /* Everyone has to know the final result */
        MPI_Bcast(&finalres, 1, MPI_FLOAT, root, MPI_COMM_WORLD);
        free(res);
        
        return finalres;
}

/*
 * Small utility function for `calcavg` to avoid code duplication.
 * Calcuates the average for a given vector
 */
static float
findavg(float *v, int len)
{
        float sum = 0.0f;
        int i = 0;

        for (; i < len; i++)
                sum += v[i];
        return (sum / (float)len);
}

/* Calculate the global average */
static float
calcavg(void)
{
        float *avgs, localavg, finalavg;

        avgs = emalloc(nproc * sizeof(float));
        localavg = findavg(localvec, localn);
        MPI_Gather(&localavg, 1, MPI_FLOAT, avgs, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

        if (rank == root)
                finalavg = findavg(avgs, nproc);
        MPI_Bcast(&finalavg, 1, MPI_FLOAT, root, MPI_COMM_WORLD);
        free(avgs);

        return finalavg;
}

/* 
 * Count how many elements are below or above average based on the
 * `flag` argument. Similar logic as with `find` above.
 */
static int
count(float avg, int flag)
{
        int *res, localres = 0, finalres = 0, i;

        res = emalloc(nproc * sizeof(int));
        for (i = 0; i < localn; i++)
                if ((flag & COUNT_BELOW_AVG && localvec[i] < avg)
                ||  (flag & COUNT_ABOVE_AVG && localvec[i] > avg))
                        localres++;
        MPI_Gather(&localres, 1, MPI_INT, res, 1, MPI_INT, root, MPI_COMM_WORLD);

        if (rank == root)
                for (i = 0; i < nproc; i++)
                        finalres += res[i];
        MPI_Bcast(&finalres, 1, MPI_INT, root, MPI_COMM_WORLD);
        free(res);

        return finalres;
}

/* Calculate the global variance */
static float
calcvar(float avg)
{
        float *vars, localvar = 0.0f, finalvar = 0.0f;
        int i;

        for (i = 0; i < localn; i++)
                localvar += (localvec[i] - avg) * (localvec[i] - avg);

        vars = emalloc(nproc * sizeof(float));
        MPI_Gather(&localvar, 1, MPI_FLOAT, vars, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

        if (rank == root) {
                for (i = 0; i < nproc; i++)
                        finalvar += vars[i];
                finalvar /= (float)n - 1;
        }
        MPI_Bcast(&finalvar, 1, MPI_FLOAT, root, MPI_COMM_WORLD);
        free(vars);

        return finalvar;
}

/* Generate D. A vector where each element is 
 * ((xi - xmin) / (xmax - xmin)) * 100.
*/
static float *
calcd(float xmin, float xmax)
{
        float *locald, *finald;
        int i;

        locald = emalloc(localn * sizeof(float));
        finald = emalloc(n * sizeof(float));

        for (i = 0; i < localn; i++)
                locald[i] = ((localvec[i] - xmin) / (xmax - xmin)) * 100;

        MPI_Gatherv(locald, localn, MPI_FLOAT, finald, scounts, displs,
                MPI_FLOAT, root, MPI_COMM_WORLD);

        free(locald);

        return finald;
}

/* Find global max and MAXLOC */
static Pair
findmax(float *d)
{
        Pair in, out;
        int i = 1;

        in.val = *d;
        in.i = 0;
        for (; i < n; i++) {
                if (in.val < d[i]) {
                        in.val = d[i];
                        in.i = i;
                }
        }
        in.i += rank * localn;
        MPI_Reduce(&in, &out, 1, MPI_FLOAT_INT, MPI_MAXLOC, root, MPI_COMM_WORLD);

        return out;
}

/* Calucate the prefix sums of `vec`. Only world when
 * n == nproc
 */
static float *
calcpfxsums(void)
{
        float *pfxsums;
        float sum = 0.0f;

        pfxsums = emalloc(n * sizeof(float));

        /* Scan each local vector and assign the result to `sum`. */
        MPI_Scan(localvec, &sum, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
        /* Be in sync. */
        MPI_Barrier(MPI_COMM_WORLD);
        /* Get results in `pfxsums` */
        MPI_Gather(&sum, 1, MPI_FLOAT, pfxsums, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

        return pfxsums;
}

/* Utility function to print a vector in a prettier way. */
static void
printv(const char *str, const float *v)
{
        int i = 0;
        
        printf("%s [", str);
        for (; i < n; i++)
                printf("%.4f%s", v[i], i != n-1 ? ", " : "");
        printf("]\n");
}

/* Error checking `malloc(3)`. */
static void *
emalloc(size_t nb)
{
        void *p;

        if ((p = malloc(nb)) == NULL) {
                fputs("cannot allocate memory", stderr);
                exit(EXIT_FAILURE);
        }
        return p;
}

int
main(int argc, char *argv[])
{
        Pair dmax;
        float avg, var, xmin, xmax;
        float *d, *pfxsums;
        int belowavg, aboveavg;
        int i, rc;

        if ((rc = MPI_Init(&argc, &argv)) != 0) {
                fprintf(stderr, "%s: cannot initialize MPI.\n", argv[0]);
                MPI_Abort(MPI_COMM_WORLD, rc);
        }
        MPI_Comm_size(MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        /* Read global vector. */
        if (rank == root) {
                n = input("N: ", 0);
                vec = emalloc(n * sizeof(float));
                for (i = 0; i < n; i++)
                        vec[i] = input("vec[%d]: ", i);
        }

        /* Send `n` to everyone. */
        MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);

        /* Will be used for `MPI_Scatterv(3)` and `MPI_Gatherv(3)` later on. */
        scounts = emalloc(nproc * sizeof(int));
        displs = emalloc(nproc * sizeof(int));
        for (i = 0; i < nproc; i++) {
                /* make it work even if `n` is not a multiple of `nproc`. */
                scounts[i] = (i != nproc - 1) ? n / nproc : n / nproc + n % nproc;
                /* take the last `scounts` so that we don't offset +1 each time. */
                displs[i] = i * scounts[i != 0 ? i-1 : i];
        }

        /* 
         * Each local `n` is the same as the `scounts` of each process, so we
         * assign it to `localn` for readablity.
         */
        localn = scounts[rank];
        localvec = emalloc(localn * sizeof(float));

        /* Scatter the array to each process. */
        MPI_Scatterv(vec, scounts, displs, MPI_FLOAT, localvec, localn,
                MPI_FLOAT, root, MPI_COMM_WORLD);
        
        /* Part 0.1 - Calculate global minimum and maximum. */
        xmin = find(FIND_XMIN);
        xmax = find(FIND_XMAX); 

        /* Part 0.2 - Calculate average. */
        avg = calcavg();

        /* Part 1 - Find how many elements are above or below average. */
        belowavg = count(avg, COUNT_BELOW_AVG);
        aboveavg = count(avg, COUNT_ABOVE_AVG);

        /* Part 2 - Calculate variance. */
        var = calcvar(avg);

        /* Part 3 - Generate D. */
        d = calcd(xmin, xmax);

        /* Part 4 - Find dmax and dmaxloc. */
        dmax = findmax(d);

        /* Part 5 - Prefix sums of `vec`. */
        pfxsums = calcpfxsums();

        /* Print all results */
        if (rank == root) {
                printf("\n");
                printv("X:              ", vec);
                printf("Average:         %.4f\n", avg);
                printf("Xmin:            %.4f\n", xmin);
                printf("Xmax:            %.4f\n", xmax);
                printf("Below Average:   %d\n", belowavg);
                printf("Above Average:   %d\n", aboveavg);
                printf("Variance:        %.4f\n", var);
                printv("D:              ", d);
                printf("Dmax:            %.4f\n", dmax.val);
                printf("Dmaxloc:         %d\n", dmax.i);
                printv("Prefix Sums:    ", pfxsums);
        }

        free(scounts);
        free(displs);
        free(vec);
        free(localvec);
        free(d);
        free(pfxsums);

        MPI_Finalize();

        return 0;
}
