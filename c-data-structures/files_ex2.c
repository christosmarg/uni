#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
        char name[50];
        float grade;
        int id;
};

int
main(int argc, char *argv[])
{
        FILE *fp;
        struct Student *s;

        if ((s = malloc(sizeof(struct Student))) == NULL) {
                fputs("malloc failed\n", stderr);
                return 1;
        }

        if ((fp = fopen("data", "r")) == NULL) {
                fputs("fopen failed\n", stderr);
                return 1;
        }

        while (fscanf(fp, "%d %s %f", &s->id, s->name, &s->grade) != EOF)
                printf("%d %s %.2f\n", s->id, s->name, s->grade);

        fclose(fp);
        free(s);

        return 0;
}
