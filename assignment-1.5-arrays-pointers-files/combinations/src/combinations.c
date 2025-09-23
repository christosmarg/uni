#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "combinations.h"

#define COMBSN 6


int get_n(const char *varName)
{
    int num;

    do
    {
        printf("%s (6 < N <= 49): ", varName);
        scanf("%d", &num);
    } while (num <= 6 || num > 49);

    return num;
}


int *fill_array(int N)
{
    int *arr, num, i = 0;

    arr = (int *)malloc(N * sizeof(int));

    if (arr == NULL)
    {
        printf("Not enough memory, error.\n");
        exit(1);
    }
    else
    {    
        do
        {
            printf("arr[%d]: ", i);
            scanf("%d", &num);

            if (num >= 1 && num <= 49)
            {
                if (i == 0)
                {
                    *(arr + i) = num;
                    i++;
                }
                else
                {
                    if (!exists_in_array(arr, N, num))
                    {
                        *(arr + i) = num;
                        i++;
                    }
                    else
                        printf("Give a different number.\n");
                }
            }
            else
                printf("Give a number in [1, 49].\n");
                
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


void combinations(int *arr)
{
    int i, j, temp;

    for (i = 1; i <= COMBSN; i++)
    {
        for (j = 0; j < COMBSN-1; j++) 
        {
            temp = *(arr + j);
            *(arr + j) = *(arr + j + 1);
            *(arr + j + 1) = temp;
	    }
    }
}


int find_even()
{

}


int even_calc()
{

}


int sum_calc()
{

}


void print_combs()
{

}


int combinations_count(int N)
{
    int numCombinations;

    numCombinations = factorial(N) / (factorial(6) * factorial(N - 6));

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


float frequency()
{

}


char *get_filename()
{

}


bool is_subset()
{

}


void read_file()
{

}