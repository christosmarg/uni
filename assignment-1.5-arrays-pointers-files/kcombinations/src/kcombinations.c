#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "kcombinations.h"
#include "arrhandler.h"


int get_n()
{
    int N;

    do
    {
        system("clear||cls");
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
        printf("K (K < N <= 49): ");
        scanf("%d", &K);
    } while (K >= N || K > 49);

    system("clear||cls");
    
    return K;
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


void print_combs(int *arr, int N, int K, int x1, int x2, int y1, int y2)
{
    int *currComb = (int *)malloc(N * sizeof(int));
    int unFrstCond = 0, unScndCondOnly = 0, printed = 0;

    if (currComb == NULL)
    {
        printf("Error! Not enough memory, exiting...\n");
        exit(EXIT_FAILURE);
    }
    else
    {    
        combinations(arr, currComb, 0, N-1, 0, K, &printed, &unFrstCond, &unScndCondOnly, x1, x2, y1, y2);
        print_other(N, K, unFrstCond, unScndCondOnly, printed);
    }

    free(currComb);
}


void combinations(int *arr, int *currComb, int start, int end, int index, int K, int *printed, int *unFrstCond, int *unScndCondOnly, int x1, int x2, int y1, int y2) 
{
    int i, j;
    
    if (index == K) 
    { 
        for (j = 0; j < K; j++) 
        {
            if (even_calc(currComb, K, x1, x2) && sum_comb_calc(currComb, K, y1, y2))
            {
                printf("%d ", *(currComb + j));
                if (j == K - 1) { (*printed)++; printf("\n"); }
            } // add freq
        }
        if (!even_calc(currComb, K, x1, x2) && sum_comb_calc(currComb, K, y1, y2)) (*unFrstCond)++;
        if (!sum_comb_calc(currComb, K, y1, y2)) (*unScndCondOnly)++;
        return;
    } 

    for (i = start; i <= end && end-i+1 >= K-index; i++) 
    { 
        *(currComb + index) = *(arr + i);
        combinations(arr, currComb, i+1, end, index+1, K, printed, unFrstCond, unScndCondOnly, x1, x2, y1, y2); 
    }
}


bool even_calc(int *arr, int K, int x1, int x2)
{
    int numEven = 0, i;

    for (i = 0; i < K; i++)
        if (*(arr + i) % 2 == 0) numEven++;

    return (numEven >= x1 && numEven <= x2) ? true : false;
}


bool sum_comb_calc(int *arr, int K, int y1, int y2)
{
    int sumNums = 0, i;

    for (i = 0; i < K; i++)
        sumNums += *(arr + i);
    
    return (sumNums >= y1 && sumNums <= y2) ? true : false;
}


int frequency()
{

}


long int combinations_count(int N, int K) // wtf ???????
{
    return (factorial(N) / (factorial(K) * factorial(N - K)));
}


long double factorial(int num)
{
    int i;
    long double fac;
    if (num == 0) return -1;
    else for (i = 1, fac = 1; i <= num; i++) fac *= i;
    return fac;
}


void print_other(int N, int K, int unFrstCond, int unScndCondOnly, int printed)
{
    printf("\nTotal number of combinations %d to %d: %ld\n", N, K, combinations_count(N, K));
    printf("Number of combinations not satisfying the first condition: %d\n", unFrstCond);
    printf("Number of combinations not satisfying the second condition only: %d\n", unScndCondOnly);
    printf("Printed combinations: %d\n", printed);
}
