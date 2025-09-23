#include <stdio.h>
#include <string.h>

/* 
 * Make a student structure, assign a pointer to it and modify
 * it using the pointer
 */

struct Student {
        char name[32];
        float avg;
};

int
main(int argc, char *argv[])
{
        struct Student stud = {"Foo Bar", 7.4f};
        struct Student *ptr;

        ptr = &stud;
        
        printf("stud.name: %s | stud.avg: %.2f\n", stud.name, stud.avg);
        strcpy(ptr->name, "Bar Baz");
        printf("ptr->name: %s | ptr->avg: %.2f\n", ptr->name, ptr->avg);

        return 0;
}
