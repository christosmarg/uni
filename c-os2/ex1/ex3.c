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

static char *argv0;

static void *
calcsum(void *tid)
{
        printf("td: %ld\n", (long)tid);
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
        pthread_t *tds;
        FILE *fp;
        int *arr;
        long i;
        long n;
        int nt;

        argv0 = *argv++;

        do {
                /* we cannot have < 0 threads */
                printf("p: ");
                scanf("%d", &nt);
        } while (nt < 0);

        do {
                /* make sure `n` is positive and also a multiple of `nt` */
                printf("n: ");
                scanf("%ld", &n);
        } while (n < 0 || n % nt != 0);

        if ((tds = malloc(nt * sizeof(pthread_t))) == NULL)
                die("malloc");

        if ((arr = malloc(n * sizeof(int))) == NULL)
                die("malloc:");

        /* 
         * if an argument was passed, use it as a file to read from,
         * otherwise read from stdin.
         */
        if (*argv == NULL)
                fp = stdin;
        else
                if ((fp = fopen(*argv, "r")) == NULL)
                        die("fopen");
        for (i = 0; i < n; i++)
                fscanf(fp, "%d", &arr[i]);
        (void)fclose(fp);

        for (i = 0; i < n; i++) {
                if (pthread_create(&tds[i], NULL, calcsum, (void *)i) != 0)
                        die("pthread_create");
                /* TODO: :-) */
                if (pthread_join(tds[i], NULL) != 0)
                        die("pthread_join");
        }
        pthread_exit(NULL);

        free(tds);
        free(arr);

        return 0;
}
