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

        if ((fp = fopen("data", "w")) == NULL) {
                fputs("fopen failed\n", stderr);
                return 1;
        }

        for (;;) {
                printf("Name: ");
                fgets(s->name, sizeof(s->name), stdin);
                s->name[strlen(s->name) - 1] = '\0';
                printf("ID: ");
                scanf("%d", &s->id);
                getchar();
                printf("Grade: ");
                scanf("%f", &s->grade);
                getchar();

                if (s->id < 0)
                        break;
                fprintf(fp, "%d %s %.2f\n", s->id, s->name, s->grade);
        }

        fclose(fp);
        free(s);

        return 0;
}
