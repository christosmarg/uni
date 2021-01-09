#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/* constants */
#define FIND_XMIN       1 << 0
#define FIND_XMAX       1 << 1
#define COUNT_BELOW_AVG 1 << 2
#define COUNT_ABOVE_AVG 1 << 3

struct Pair {
        float val;      /* max value in array */
        int i;          /* index of max */
};

/* function declarations */
static float     input(const char *, int);
static float     find(int);
static float     findavg(float *, int);
static float     calcavg(void);
static int       count(float, int);
static float     calcvar(float);
static float    *calcd(float, float);
struct Pair      findmax(float *);
static float    *calcpfxsums(void);
static void      printv(const char *, const float *);
static void     *emalloc(size_t);

/* global variables */
static int rank, nproc, root = 0;
static int *scounts, *displs;
static float *vec, *localvec;
static int n, localn;

/* function implementations */
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

static float
find(int flag)
{
        float localres = *localvec;
        float finalres = localres;
        float *res;
        int i;

        res = emalloc(nproc * sizeof(float));
        for (i = 0; i < localn; i++)
                if ((flag & FIND_XMIN && localvec[i] < localres)
                ||  (flag & FIND_XMAX && localvec[i] > localres))
                        localres = localvec[i];
        MPI_Gather(&localres, 1, MPI_FLOAT, res, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

        if (rank == root)
                for (i = 0; i < nproc; i++)
                        if ((flag & FIND_XMIN && res[i] < finalres)
                        ||  (flag & FIND_XMAX && res[i] > finalres))
                                finalres = res[i];

        MPI_Bcast(&finalres, 1, MPI_FLOAT, root, MPI_COMM_WORLD);
        free(res);
        
        return finalres;
}

static float
findavg(float *vec, int len)
{
        float sum = 0.0f;
        int i = 0;

        for (; i < len; i++)
                sum += vec[i];
        return (sum / (float)len);
}

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

struct Pair
findmax(float *d)
{
        struct Pair in, out;
        float *locald;
        int i = 0;

        locald = emalloc(localn * sizeof(float));
        MPI_Scatterv(d, scounts, displs, MPI_FLOAT, locald, localn, MPI_FLOAT,
                root, MPI_COMM_WORLD);

        in.val = *locald;
        in.i = 0;
        for (; i < localn; i++) {
                if (in.val < locald[i]) {
                        in.val = locald[i];
                        in.i = i;
                }
        }
        in.i += rank * localn;
        MPI_Reduce(&in, &out, 1, MPI_FLOAT_INT, MPI_MAXLOC, root, MPI_COMM_WORLD);
        free(locald);

        return out;
}

static float *
calcpfxsums(void)
{
        float *localsums, *finalsums;
        float sum = 0.0f;

        localsums = emalloc(nproc * sizeof(float));
        finalsums = emalloc(n * sizeof(float));

        MPI_Scan(localsums, &sum, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
        /*MPI_Gather(&sum, 1, MPI_FLOAT, finalsums, 1, MPI_FLOAT, root, MPI_COMM_WORLD);*/

        free(localsums);

        return finalsums;
}

static void
printv(const char *str, const float *v)
{
        int i = 0;
        
        printf("%s [", str);
        for (; i < n; i++)
                printf("%.4f%s", v[i], i != n-1 ? ", " : "");
        printf("]\n");
}

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
        struct Pair dmax;
        float avg, var, xmin, xmax;
        float *d, *pfxsums;
        int belowavg, aboveavg;
        int i;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

        if (rank == root) {
                n = input("N: ", 0);
                vec = emalloc(n * sizeof(float));
                for (i = 0; i < n; i++)
                        vec[i] = input("vec[%d]: ", i);
        }

        /* move? */
        MPI_Bcast(&n, 1, MPI_INT, root, MPI_COMM_WORLD);

        scounts = emalloc(nproc * sizeof(int));
        displs = emalloc(nproc * sizeof(int));
        
        for (i = 0; i < nproc; i++) {
                /* TODO: explain */
                scounts[i] = (i != nproc - 1) ? n / nproc : n / nproc + n % nproc;
                displs[i] = i * scounts[i != 0 ? i-1 : i];
        }

        localn = scounts[rank];
        localvec = emalloc(localn * sizeof(float));

        MPI_Scatterv(vec, scounts, displs, MPI_FLOAT, localvec, localn,
                MPI_FLOAT, root, MPI_COMM_WORLD);
        
        /* part 0.1 - calculate min and max */
        xmin = find(FIND_XMIN);
        xmax = find(FIND_XMAX); 

        /* part 0.2 - calculate average */
        avg = calcavg();

        /* part 1 - find how many elements are above or below average */
        belowavg = count(avg, COUNT_BELOW_AVG);
        aboveavg = count(avg, COUNT_ABOVE_AVG);

        /* part 2 - calculate variance */
        var = calcvar(avg);

        /*
         * part 3 - make a new vector where each element is:
         * ((xi - xmin) / (xmax - xmin)) * 100
         */
        d = calcd(xmin, xmax);

        /* part 4 - find dmax and dmaxloc */
        dmax = findmax(d);

        /* part 5 - prefixs sum of vec */
        pfxsums = calcpfxsums();

        /* print all results */
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
