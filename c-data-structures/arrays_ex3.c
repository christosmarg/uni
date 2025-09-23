#include <stdio.h>
#include <stdlib.h>

#define ARRLEN(x) (sizeof(x) / sizeof(x[0]))

/* Modify arrays_ex2.c to get the array's elements from stdin */

int
main(int argc, char *argv[])
{
        float sum, avg;
        int arr[10], i;
        int max, min, maxloc, minloc;

        sum = 0;
        for (i = 0; i < ARRLEN(arr); i++) {
                do {
                        printf("arr[%d]: ", i);
                        scanf("%d", &arr[i]);
                        getchar();
                } while (arr[i] < 0 || arr[i] > 100);

                sum += arr[i];
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
