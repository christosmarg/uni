#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
        char name[50];
        float grade;
        int id;
        struct Student *left;
        struct Student *right;
};

static struct Student *
createstud(struct Student *root)
{
        struct Student *s;

        if ((s = malloc(sizeof(struct Student))) == NULL) {
                fputs("malloc failed\n", stderr);
                exit(EXIT_FAILURE);
        }

        printf("Name: ");
        fgets(s->name, sizeof(s->name), stdin);
        s->name[strlen(s->name) - 1] = '\0';
        printf("ID: ");
        scanf("%d", &s->id);
        getchar();
        printf("Grade: ");
        scanf("%f", &s->grade);
        getchar();

        s->left = NULL;
        s->right = NULL;

        return s;

}

static void
addinorder(struct Student *root, struct Student *s)
{
        if (s->id < root->id) {
                if (root->left == NULL)
                        root->left = s;
                else
                        addinorder(root->left, s);
        } else {
                if (root->right == NULL)
                        root->right = s;
                else
                        addinorder(root->right, s);
        }
}

static void
printinorder(struct Student *root)
{
        if (root != NULL) {
                printinorder(root->left);
                printf("Name: %s | ID: %d | Grade: %.2f\n", root->name,
                        root->id, root->grade);
                printinorder(root->right);
        }
}

static float
maxgrade(struct Student *root)
{
        float max = -1, maxright = -1;

        if (root != NULL) {
                max = maxgrade(root->left);
                if (root->grade > max)
                        max = root->grade;
                maxright = maxgrade(root->right);
                if (maxright > max)
                        max = maxright;
                return max;
        }

        return max;
}

int
main(int argc, char *argv[])
{
        struct Student *root = NULL, *stud;
        float max;
        int ch = -1;

        while (ch != 0) {
                puts("1. Add student in order");
                puts("2. Print students in order");
                puts("3. Show maximum grade");
                puts("0. Exit");
                printf("\nYour choice: ");
                scanf("%d", &ch);
                getchar();

                switch (ch) {
                case 1:
                        stud = createstud(root);
                        if (root == NULL)
                                root = stud;
                        else
                                addinorder(root, stud);
                        break;
                case 2:
                        printinorder(root);
                        break;
                case 3:
                        if ((max = maxgrade(root)) < 0)
                                puts("Empty tree.");
                        else
                                printf("Max grade: %.2f\n", max);
                        break;
                }
        }

        return 0;
}
