#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRLEN(x) (sizeof(x) / sizeof(x[0]))

/*
 * Modify arrays_ex1.c to find max, maxloc, min, minloc,
 * and the average value
 */

int
main(int argc, char *argv[])
{
        float sum, avg;
        int arr[10], i;
        int max, min, maxloc, minloc;

        srand(time(NULL));
        sum = 0;
        for (i = 0; i < ARRLEN(arr); i++) {
                arr[i] = rand() % 101;
                sum += arr[i];
                printf("arr[%d]: %d\n", i, arr[i]);
        }

        max = min = arr[0];
        maxloc = minloc = 0;
        for (i = 0; i < ARRLEN(arr); i++) {
                if (arr[i] < min) {
                        min = arr[i];
                        minloc = i;
                }
                if (arr[i] > max) {
                        max = arr[i];
                        maxloc = i;
                }
        }

        avg = sum / (float)ARRLEN(arr);
        printf("max: %d | maxloc: %d | min: %d | minloc: %d | avg: %.2f\n",
                max, maxloc, min, minloc, avg);

        return 0;
}
