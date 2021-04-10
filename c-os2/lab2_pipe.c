#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFPAGER "/usr/bin/less"

static void
die(const char *str)
{
        perror(str);
        exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
        FILE *fp;
        char buf[BUFSIZ], *pager, *argv0;
        pid_t pid;
        int fd[2], n;

        if (argc != 2)
                die("usage: foo file");
        if ((fp = fopen(argv[1], "r")) == NULL)
                die("fopen");
        if (pipe(fd) < 0)
                die("pipe");
        
        switch (pid = fork()) {
        case -1:
                die("fork");
        case 0:
                close(fd[1]);
                if (fd[0] != STDIN_FILENO) {
                        if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
                                die("dup2");
                        close(fd[0]);
                }
                if ((pager = getenv("PAGER")) == NULL)
                        pager = DEFPAGER;
                if ((argv0 = strrchr(pager, '/')) != NULL)
                        argv0++;
                else
                        argv0 = pager;
                if (execlp(pager, argv0, NULL) < 0)
                        die("execlp");
        default:
                close(fd[0]);
                while (fgets(buf, BUFSIZ, fp) != NULL) {
                        n = strlen(buf);
                        if (write(fd[1], buf, n) != n)
                                die("write");
                }
                if (ferror(fp))
                        die("fgets");
                close(fd[1]);
                if (waitpid(pid, NULL, 0) < 0)
                        die("waitpid");
                exit(0);
        }

        return 0;
}
