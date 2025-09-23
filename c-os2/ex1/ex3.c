#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 1: Άσκηση 3 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex3.c -lpthread -o ex3`
 */

static void *calc(void *);
static void die(const char *);

static char *argv0;             /* Program name */
static int *sums;               /* Sums for each thread */
static int *arr;                /* Global vector */
static int n;                   /* `arr`'s length */
static int ntd;                 /* Number of threads */
static pthread_mutex_t mutex;   /* Mutex to prevent race conditions */

/* 
 * Each thread calculates the sum of the squares of each element in a specified
 * region in `arr`. That range is determined by the thread's ID (e.g the current
 * thread) and the number of elements that each thread has to compute. Since
 * `arr`'s length is a multiple of `ntd`, we can calculate the number of elements
 * each thread will compute by doing `n / ntd`.
 *
 * For example, `ntd = 2` and `n = 4`, and `arr [1, 2, 3, 4]`.
 * Each thread will compute `n / ntd = 2` elements.
 *
 * Thread 0 will operate in the region:
 *      `td * (n / ntd) = 0 * 2 = 0` to 
 *      `(td + 1) * (n / ntd) - 1 = (0 + 1) * 2 - 1 = 1`
 *
 * Thread 1 will operate in the region:
 *      `1 * 2 = 2` to `(1 + 1) * 2 - 1 = 3`
 *
 * So effectively, each thread will be assigned to compute an equal amount of
 * elements.
 */
static void *
calc(void *tid)
{
        long td;
        int localsum;
        int i;

        if (pthread_mutex_lock(&mutex) != 0)
                die("pthread_mutex_lock");

        td = (long)tid;
        localsum = 0;
        for (i = td * (n / ntd); i < (td + 1) * (n / ntd); i++) {
                printf("td: %ld | arr[%d]: %d\n", td, i, arr[i]);
                sums[td] += arr[i] * arr[i];
        }
        if (pthread_mutex_unlock(&mutex) != 0)
                die("pthread_mutex_unlock");

        return NULL;
}

static void
die(const char *str)
{
        fprintf(stderr, "%s: ", argv0);
        perror(str);
        exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
        pthread_t *tds; /* Threads */
        FILE *fp;       /* Either stdin or a text file */
        int totalsum;   /* Total sum */
        long i;         /* Counter */

        argv0 = *argv++;

        /* 
         * If an argument was passed, use it as a file to read from,
         * otherwise read from stdin.
         */
        if (*argv == NULL)
                fp = stdin;
        else if ((fp = fopen(*argv, "r")) == NULL)
                die("fopen");

        /* 
         * We do error checking for `n` and `ntd` but in case we read from a
         * file the program might break if the data is wrong (i.e fails the
         * error checks at least once) since it will keep going further down
         * into the file. The same doesn't apply for when reading from stdin --
         * we can just give it a new number until it's correct.
         */
        do {
                printf("p: ");
                fscanf(fp, "%d", &ntd);
                /* Cannot have < 0 threads. */
        } while (ntd < 0);

        do {
                printf("n: ");
                fscanf(fp, "%d", &n);
                /* Make sure `n` is positive and also a multiple of `ntd`. */
        } while (n < 0 || n % ntd != 0);

        if ((tds = malloc(ntd * sizeof(pthread_t))) == NULL)
                die("malloc");
        if ((arr = malloc(n * sizeof(int))) == NULL)
                die("malloc");
        if ((sums = malloc(ntd * sizeof(int))) == NULL)
                die("malloc");

        /* Read the vector. */
        for (i = 0; i < n; i++)
                fscanf(fp, "%d", &arr[i]);
        (void)fclose(fp);

        if (pthread_mutex_init(&mutex, NULL) != 0)
                die("pthread_mutex_init");
        /* 
         * Start multithreading. For each thread we assign `calc`
         * to be the callback function that each thread will call.
         */
        for (i = 0; i < ntd; i++) {
                if (pthread_create(&tds[i], NULL, calc, (void *)i) != 0)
                        die("pthread_create");
                if (pthread_join(tds[i], NULL) != 0)
                        die("pthread_join");
        }

        totalsum = 0;
        while (ntd--)
                totalsum += *sums++;
        printf("total sum: %d\n", totalsum);

        free(tds);
        free(arr);
        free(sums);
        (void)pthread_mutex_destroy(&mutex);
        pthread_exit(NULL);

        return 0;
}
