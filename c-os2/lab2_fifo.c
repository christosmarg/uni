#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
        FILE *cfp, *pfp;
        char coolfifo[] = "/tmp/coolfifo";
        pid_t pid;
        int ret, val;

        if ((ret = mkfifo(coolfifo, 0600)) < 0)
                err(1, "mkfifo");
        switch (pid = fork()) {
        case -1:
                err(1, "fork");
        case 0:
                if ((cfp = fopen(coolfifo, "w")) == NULL)
                        err(1, "fopen");
                ret = fprintf(cfp, "%d", 1000);
                fflush(cfp);
                exit(0);
        default:
                if ((pfp = fopen(coolfifo, "r")) == NULL)
                        err(1, "fopen");
                if ((ret = fscanf(pfp, "%d", &val)) < 0)
                        err(1, "fscanf");
                fclose(pfp);
                printf("parent: recv: %d\n", val);
                unlink(coolfifo);
                exit(0);
        }

        return 0;
}
