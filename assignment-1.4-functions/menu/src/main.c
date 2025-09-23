#include <stdio.h>
#include "menu.h"


int main(int argc, char **argv)
{
    int a, b;

    printf("A: ");
    scanf("%d", &a);
    printf("B: ");
    scanf("%d", &b);
    
    menu(a, b);

    return 0;
}