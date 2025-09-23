#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "combinations.h"

#define COMBSN 6


int get_n()
{
    int N;

    do
    {
        printf("N (6 < N <= 49): ");
        scanf("%d", &N);
    } while (N <= 6 || N > 49);

    return N;
}


void x_pair(int *x1, int *x2)
{
    do
    {
        printf("x1: ");
        scanf("%d", x1);
        printf("x2: ");
        scanf("%d", x2);
    } while (*x1 < 0 || *x1 > *x2 || *x2 > 6);
}


void y_pair(int *y1, int *y2)
{
    do
    {
        printf("y1: ");
        scanf("%d", y1);
        printf("y2: ");
        scanf("%d", y2);
    } while (*y1 < 21 || *y1 > *y2 || *y2 > 279);
}


void combinations(int *arr, int x1, int x2, int y1, int y2)
{
    int i, j, k, l, m, n;

    for (i = 0; i < COMBSN-5; i++)
        for (j = i+1; j < COMBSN-4; j++)
            for (k = j+1; k < COMBSN-3; k++)
                for (l = k+1; l < COMBSN-2; l++)
                    for (m = l+1; m < COMBSN-1; m++)
                        for (n = m+1; n < COMBSN; n++)
                        {
                            printf("%d %d %d %d %d %d", *(arr + i), *(arr + j), *(arr + k), *(arr + l), *(arr + m), *(arr + n));
                            printf("\n");
                        }
}


int combinations_count(int N)
{
    return factorial(N) / (factorial(COMBSN) * factorial(N - COMBSN));
}


int factorial(int num)
{
    int i, fac;
    for (i = 1, fac = 1; i <= num; i++) fac *= i;
    return fac;
}