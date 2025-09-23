#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "combinations.h"
#include "ccolors.h"

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


int get_k(int N)
{
    int K;

    do
    {
        printf("K: ");
        scanf("%d", &K);
    } while (K > N || K < 0);

    return K;
}


int *fill_array(int N)
{
    int *arr, num, i = 0;

    arr = (int *)malloc(N * sizeof(int));

    if (arr == NULL)
    {
        set_color(BOLD_RED);
        printf("Error! Not enough memory, exiting...\n");
        set_color(STANDARD);
        exit(EXIT_FAILURE);
    }
    else
    {    
        do
        {
            printf("arr[%d]: ", i);
            scanf("%d", &num);

            if (num >= 1 && num <= 49)
            {
                if (i == 0) { *(arr + i) = num; i++; }
                else
                {
                    if (!exists_in_array(arr, N, num)) { *(arr + i) = num; i++; }
                    else printf("Give a different number.\n");
                }
            }
            else printf("Give a number in [1, 49].\n");
        } while (i < N);
    }

    return arr;
}


bool exists_in_array(int *arr, int N, int num)
{
    int *arrEnd = arr + N - 1;

    while (arr <= arrEnd && *arr != num)
        arr++;
    
    if (arr <= arrEnd)
        return true;
    else
        return false;
}


int *sort(int *arr)
{

}


void x_pair(int *x1, int *x2)
{
    do
    {
        printf("x1: ");
        scanf("%d", x1);
        printf("x2: ");
        scanf("%d", x2);
    } while (*x1 < 0 || *x1 > *x2 || *x2 > 6); // 0 ≤ Χ1 ≤ Χ2  ≤ 6
}


void y_pair(int *y1, int *y2)
{
    do
    {
        printf("y1: ");
        scanf("%d", y1);
        printf("y2: ");
        scanf("%d", y2);
    } while (*y1 < 21 || *y1 > *y2 || *y2 > 279); // 21 ≤ Υ1 ≤ Υ2 ≤ 279
}


void combinations(int *arr, int x1, int x2, int y1, int y2)
{
    int i, j, k, l, m, n;

    for (i=0; i < COMBSN-5; i++)
        for (j = i+1; j < COMBSN-4; j++)
            for (k = j+1; k < COMBSN-3; k++)
                for (l = k+1; l < COMBSN-2; l++)
                    for (m= l+1; m < COMBSN-1; m++)
                        for (n = m+1; n < COMBSN; n++)
                        {
                            printf("%d %d %d %d %d %d", *(arr + i), *(arr + j), *(arr + k), *(arr + l), *(arr + m), *(arr + n));
                            printf("\n");
                        }
}


int even_calc(int *arr)
{

}


bool belongs_x(int numEven, int x1, int x2)
{

}


int sum_calc(int *arr)
{

}


bool belongs_y(int sumNums, int y1, int y2)
{

}


void print_combs(int *arr)
{
    int i;

    for (i = 0; i < COMBSN; i++)
        printf("%d ", *(arr + i));
    printf("\n");
}


void print(int N)
{

}



int combinations_count(int N)
{
    int numCombinations;

    numCombinations = factorial(N) / (factorial(COMBSN) * factorial(N - COMBSN));

    return numCombinations;
}


int factorial(int num)
{
    int i, fac;

    for (i = 1, fac = 1; i <= num; i++)
        fac *= i;

    return fac;
}


int sum_comb_calc()
{

}


int not_printed()
{

}


int not_first_condition()
{

}


int not_second_condition_only()
{

}


int frequency()
{

}