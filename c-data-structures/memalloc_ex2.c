#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Make N student strucutre, allocate memory for them and
 * assign values to them from stdin.
 */

struct Student {
        char name[32];
        int id;
        float grade;
};

int
main(int argc, char *argv[])
{
        struct Student *stud;
        int n, i;
        float sum;

        do {
                printf("How many students? ");
                scanf("%d", &n);
                getchar();
        } while (n <= 0);

        if ((stud = malloc(n * sizeof(struct Student))) == NULL)
                return 1;

        sum = 0.0f;
        for (i = 0; i < n; i++) {
                printf("stud[%d].name: ", i);
                fgets(stud[i].name, 32, stdin);

                printf("stud[%d].id: ", i);
                scanf("%d", &stud[i].id);
                getchar();

                printf("stud[%d].grade: ", i);
                scanf("%f", &stud[i].grade);
                getchar();

                sum += stud[i].grade;
        }

        printf("avg: %.2f\n", sum / (float)n);

        return 0;
}
