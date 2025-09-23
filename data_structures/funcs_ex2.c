#include <stdio.h>

/* 
 * Write a function that computes the basic operations.
 * Take the first 2 arguments by value and the rest
 * by pointer.
 */

static void
calc(float x, float y, float *sum, float *diff, float *prod, float *ratio)
{
        *sum = x + y;
        *diff = x - y;
        *prod = x * y;
        if (y != 0)
                *ratio = x / y;
}

int
main(int argc, char *argv[])
{
        float x = 20, y = 10;
        float sum, diff, prod, ratio = 0;

        calc(x, y, &sum, &diff, &prod, &ratio);
        printf("x: %.2f | y: %.2f | sum: %.2f | diff: %.2f | prod: %.2f | ratio: %.2f\n",
                x, y, sum, diff, prod, ratio);

        return 0;
}
