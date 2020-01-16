#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fcombinations.h"
#include "ccolors.h"

#define COMBSN 6


void read_file(char **argv)
{
    FILE *dataFile = fopen(argv[1], "r");

    if (dataFile == NULL)
    {
        set_color(BOLD_RED);
        printf("Error opening the file, exiting...\n");
        set_color(STANDARD);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Cool\n");
        // fscanf();
    }

    fclose(dataFile);
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