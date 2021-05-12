#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void
die(const char *str)
{
        perror(str);
        exit(1);
}

int
main(int argc, char *argv[])
{
        FILE *cfp, *pfp;
        char coolfifo[] = "/tmp/coolfifo";
        pid_t pid;
        int ret, val;

        if ((ret = mkfifo(coolfifo, 0600)) < 0)
                die("mkfifo");
        switch (pid = fork()) {
        case -1:
                die("fork");
        case 0:
                if ((cfp = fopen(coolfifo, "w")) == NULL)
                        die("fopen");
                ret = fprintf(cfp, "%d", 1000);
                fflush(cfp);
                exit(0);
        default:
                if ((pfp = fopen(coolfifo, "r")) == NULL)
                        die("fopen");
                if ((ret = fscanf(pfp, "%d", &val)) < 0)
                        die("fscanf");
                fclose(pfp);
                printf("parent: recv: %d\n", val);
                unlink(coolfifo);
                exit(0);
        }

        return 0;
}
