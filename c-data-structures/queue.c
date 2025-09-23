#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
        char name[50];
        float grade;
        int id;
        struct Student *next;
};

struct Student *head, *tail;

static void
enqueue(struct Student *s)
{
        struct Student *p;

        if ((p = malloc(sizeof(struct Student))) == NULL) {
                fputs("malloc failed\n", stderr);
                exit(EXIT_FAILURE);
        }

        *p = *s;
        p->next = NULL;
        if (tail == NULL)
                head = p;
        else
                tail->next = p;
        tail = p;
}

static void
dequeue(void)
{
        struct Student *p;

        if (head != NULL) {
                p = head;
                head = head->next;
                free(p);
                if (head == NULL)
                        tail = NULL;
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
        tail = NULL;

        while (ch != 0) {
                puts("1. Enqueue");
                puts("2. Dequeue");
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
                        enqueue(&stud);
                        break;
                case 2:
                        dequeue();
                        break;
                case 3:
                        print();
                        break;
                }
        }

        return 0;
}
