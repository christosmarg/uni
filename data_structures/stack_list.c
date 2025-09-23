#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
        char name[50];
        float grade;
        int id;
        struct Student *next;
};

struct Student *head;

static void
push(struct Student *s)
{
        struct Student *p;

        if ((p = malloc(sizeof(struct Student))) == NULL) {
                fputs("malloc failed\n", stderr);
                exit(EXIT_FAILURE);
        }

        *p = *s;
        p->next = head;
        head = p;
}

static void
pop(void)
{
        struct Student *p;

        if (head != NULL) {
                p = head;
                head = head->next;
                free(p);
        }
}

static void
print(void)
{
        struct Student *p;

        for (p = head; p != NULL; p = p->next)
                printf("Name: %s | ID: %d | Grade: %.2f\n", p->name, p->id, p->grade);
}

int
main(int argc, char *argv[])
{
        struct Student stud;
        int ch = -1;

        head = NULL;

        while (ch != 0) {
                puts("1. Push");
                puts("2. Pop");
                puts("3. Print");
                puts("0. Exit");
                printf("\nYour choice: ");
                scanf("%d", &ch);
                getchar();

                switch (ch) {
                case 1:
                        printf("Name: ");
                        fgets(stud.name, sizeof(stud.name), stdin);
                        stud.name[strlen(stud.name) - 1] = '\0';
                        printf("ID: ");
                        scanf("%d", &stud.id);
                        getchar();
                        printf("Grade: ");
                        scanf("%f", &stud.grade);
                        getchar();
                        push(&stud);
                        break;
                case 2:
                        pop();
                        break;
                case 3:
                        print();
                        break;
                }
        }

        return 0;
}
