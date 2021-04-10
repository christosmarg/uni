#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * Εργαστήριο ΛΣ2 (Δ6) / Εργασία 1: Άσκηση 2 / 2020-2021
 * Ονοματεπώνυμο: Χρήστος Μαργιώλης
 * ΑΜ: 19390133
 * Τρόπος μεταγλώττισης: `cc ex2.c -o ex2`
 */

static char *argv0;

/* 
 * Print a process' info. `n` indicates which process is being
 * printed -- for example `printproc(2)` will print P2.
 */
static void
printproc(int n)
{
        printf("p: %d\tpid: %d\tppid: %d\n", n, getpid(), getppid());
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
        char buf[32];   /* message buffer */
        int fd[2];      /* pipe(2) file descriptors */
        int n;          /* bytes returned from read(2) */
        int i = 3;      /* P2 will create 3 child procs */

        argv0 = *argv;

        /* create pipe */
        if (pipe(fd) < 0)
                die("pipe");

        printproc(0);

        /* create P1 */
        switch (fork()) {
        case -1:
                die("fork");
        case 0:
                printproc(1);
                (void)strcpy(buf, "Hello from your first child\n");
                /* close read fd and send message to P0 */
                (void)close(fd[0]);
                if (write(fd[1], buf, sizeof(buf)) != sizeof(buf))
                        die("write");
                exit(EXIT_SUCCESS);
        default:
                /* close write fd and receive message from P1 */
                (void)close(fd[1]);
                if ((n = read(fd[0], buf, sizeof(buf))) != sizeof(buf))
                        die("read");
                if (write(STDOUT_FILENO, buf, n) != n)
                        die("write");
                if (wait(NULL) == -1)
                        die("wait");
                /* create P2 */
                switch (fork()) {
                case -1:
                        die("fork");
                case 0:
                        printproc(2);
                        /* create P3, P4 and P5 */
                        while (i--) {
                                switch (fork()) {
                                case -1:
                                        die("fork");
                                case 0:
                                        printproc(2 + i + 1);
                                        exit(EXIT_SUCCESS);
                                default:
                                        /* wait for all children to exit first */
                                        if (wait(NULL) == -1)
                                                die("wait");
                                }
                        }
                        exit(EXIT_SUCCESS);
                default:
                        /* wait for P2 to exit */
                        if (wait(NULL) == -1)
                                die("waitpid");
                }
                if (execl("/bin/ps", "ps", NULL) == -1)
                        die("execl");
        }

        return 0;
}
