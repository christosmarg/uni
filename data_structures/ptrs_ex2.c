#include <stdio.h>

#define ARRLEN(x) (sizeof(x) / sizeof(x[0]))

/* 
 * Make an array and print its contents using both
 * indexing and pointer arithemtic
 */

int
main(int argc, char *argv[])
{
        int arr[5] = {1, 2, 3, 4, 5};
        int i = 0;

        for (; i < ARRLEN(arr); i++) {
                printf("arr[%d]: %d | addr: %p\n", i, arr[i], &arr[i]);
                printf("*(arr + %d): %d | addr: %p\n", i, arr[i], &arr[i]);
        }

        return 0;
}
