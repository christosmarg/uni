#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Make an array of 10 ints and assign random values in it */

int
main(int argc, char *argv[])
{
        int arr[10], i = 0;

        srand(time(NULL));
        for (; i < 10; i++) {
                arr[i] = rand() % 101;
                printf("arr[%d]: %d\n", i, arr[i]);
        }

        return 0;
}
