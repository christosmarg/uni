#include <stdio.h>

/* 
 * Assign a pointer to a variable and change its 
 * value using both the variable and the pointer. Then
 * print their value and addresses
 */

int
main(int argc, char *argv[])
{
        int *ptr, x = 10;

        ptr = &x;
        x += 20;
        *ptr += 30;

        printf("x: val: %d | addr: %p\n", x, &x);
        printf("ptr: val: %d | addr: %p\n", *ptr, ptr);

        return 0;
}
