#include <sys/wait.h>

#include <err.h>
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

/* 
 * Print a process' info. `n` indicates which process is being
 * printed -- for example `printproc(2)` will print P2.
 */
static void
printproc(int n)
{
	printf("p: %d\tpid: %d\tppid: %d\n", n, getpid(), getppid());
}

int
main(int argc, char *argv[])
{
	char buf[32];	/* Message buffer */
	int fd[2];	/* Pipe(2) file descriptors */
	int n;		/* Bytes returned from read(2) */
	int i = 3;	/* P2 will create 3 child procs */

	/* Create pipe */
	if (pipe(fd) < 0)
		err(1, "pipe");

	printproc(0);

	/* Create P1 */
	switch (fork()) {
	case -1:
		err(1, "fork");
	case 0:
		printproc(1);
		(void)strcpy(buf, "Hello from your first child\n");
		/* Close the read fd and send message to P0 */
		(void)close(fd[0]);
		if (write(fd[1], buf, sizeof(buf)) != sizeof(buf))
			err(1, "write");
		exit(EXIT_SUCCESS);
	default:
		/* Close the write fd and receive message from P1 */
		(void)close(fd[1]);
		if ((n = read(fd[0], buf, sizeof(buf))) != sizeof(buf))
			err(1, "read");
		/* Print the message to stdout */
		if (write(STDOUT_FILENO, buf, n) != n)
			err(1, "write");
		if (wait(NULL) < 0)
			err(1, "wait");
		/* Create P2 */
		switch (fork()) {
		case -1:
			err(1, "fork");
		case 0:
			printproc(2);
			/* create P3, P4 and P5 */
			while (i--) {
				switch (fork()) {
				case -1:
					err(1, "fork");
				case 0:
					printproc(2 + i + 1);
					exit(EXIT_SUCCESS);
				default:
					/* Wait for all children to exit first */
					if (wait(NULL) < 0)
						err(1, "wait");
				}
			}
			exit(EXIT_SUCCESS);
		default:
			/* wait for P2 to exit */
			if (wait(NULL) < 0)
				err(1, "wait");
		}
		/* 
		 * Finally, the parent process executes ps(1) after
		 * everything else has exited 
		 */
		if (execl("/bin/ps", "ps", NULL) < 0)
			err(1, "execl");
	}

	return 0;
}
