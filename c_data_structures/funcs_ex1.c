#include <stdio.h>

/* 
 * Write two swap functions. One using call by value
 * and one using call by pointer 
 */

static void
swap_val(int x, int y)
{
        int tmp;

        tmp = x;
        x = y;
        y = tmp;
}

static void
swap_ptr(int *x, int *y)
{
        int tmp;

        tmp = *x;
        *x = *y;
        *y = tmp;
}

int
main(int argc, char *argv[])
{
        int x = 10, y = 20;

        printf("x: %d | y: %d\n", x, y);
        swap_val(x, y);
        swap_ptr(&x, &y);
        printf("x: %d | y: %d\n", x, y);

        return 0;
}
