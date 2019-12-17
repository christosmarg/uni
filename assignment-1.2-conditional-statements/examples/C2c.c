#include <stdio.h>
#define t 6

int main ()
{
    int i = 7;
    switch (i)
    {
        case 3: printf ("3\n"); 
        case 5: printf ("5\n"); break;
        case 3 + 4: printf ("7\n");
        default: printf ("default\n");
        case 1: printf ("1\n"); break;
        case t: printf ("t\n");
    }
}

