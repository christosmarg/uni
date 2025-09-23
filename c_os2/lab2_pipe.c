#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFPAGER "/usr/bin/less"

static char *argv0;

int
main(int argc, char *argv[])
{
        FILE *fp;
        char buf[BUFSIZ], *pager, *argv0;
        pid_t pid;
        int fd[2], n;

	argv0 = *argv;
        if (argc != 2) {
		fprintf(stderr, "usage: %s file\n", argv0);
		return 1;
	}
        if ((fp = fopen(argv[1], "r")) == NULL)
                err(1, "fopen");
        if (pipe(fd) < 0)
                err(1, "pipe");
        
        switch (pid = fork()) {
        case -1:
                err(1, "fork");
        case 0:
                close(fd[1]);
                if (fd[0] != STDIN_FILENO) {
                        if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
                                err(1, "dup2");
                        close(fd[0]);
                }
                if ((pager = getenv("PAGER")) == NULL)
                        pager = DEFPAGER;
                if ((argv0 = strrchr(pager, '/')) != NULL)
                        argv0++;
                else
                        argv0 = pager;
                if (execlp(pager, argv0, NULL) < 0)
                        err(1, "execlp");
        default:
                close(fd[0]);
                while (fgets(buf, BUFSIZ, fp) != NULL) {
                        n = strlen(buf);
                        if (write(fd[1], buf, n) != n)
                                err(1, "write");
                }
                if (ferror(fp))
                        err(1, "fgets");
                close(fd[1]);
                if (waitpid(pid, NULL, 0) < 0)
                        err(1, "waitpid");
                exit(0);
        }

        return 0;
}
