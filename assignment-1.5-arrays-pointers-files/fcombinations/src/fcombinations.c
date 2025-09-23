#include "fcombinations.h"

int get_n(FILE *dataFile)
{
    int N;
    
    do
    {
        fscanf(dataFile, "%d\n", &N);

        printf("%d\n", N);
    } while (N <= 6 || N > 49);

    return N;
}


void x_pair(int *x1, int *x2, FILE *dataFile)
{
    do
    {
        fscanf(dataFile, "%d\n", x1);
        fscanf(dataFile, "%d\n", x2);
    } while (*x1 < 0 || *x1 > *x2 || *x2 > 6);
}


void y_pair(int *y1, int *y2, FILE *dataFile)
{
    do
    {
        fscanf(dataFile, "%d\n", y1);
        fscanf(dataFile, "%d\n", y2);
    } while (*y1 < 21 || *y1 > *y2 || *y2 > 279);
}


void print_combs(int *arr, int N, int x1, int x2, int y1, int y2)
{
    int *currComb = (int *)malloc(N * sizeof(int));
	int *freqArr = (int *)malloc(N *sizeof(int));
	int unFrstCond = 0, unScndCondOnly = 0, printed = 0;

    if (currComb == NULL)
    {
        set_color(BOLD_RED);
        printf("Error! Not enough memory, exiting...\n");
        exit(EXIT_FAILURE);
        set_color(STANDARD);
    }
    else
    {    
        combinations(arr, currComb, freqArr, 0, N-1, 0, &printed, &unFrstCond, &unScndCondOnly, x1, x2, y1, y2, N);
		print_other(N, unFrstCond, unScndCondOnly, printed, arr, freqArr);
    }

    free(currComb);
	free(freqArr);
}


void combinations(int *arr, int *currComb, int *freqArr, int start, int end, int index, int *printed, int *unFrstCond, int *unScndCondOnly, int x1, int x2, int y1, int y2, int N) 
{
    int i, j;
    
    if (index == COMBSN) 
    { 
		for (j = 0; j < COMBSN; j++) 
        {
            if (even_calc(currComb, x1, x2) && sum_comb_calc(currComb, y1, y2))
            {
                printf("%d ", *(currComb + j));
				if (j == COMBSN - 1)
				{
					frequency(freqArr, currComb, arr, N);
					(*printed)++;
					printf("\n");
				}
            }
        }
        if (!even_calc(currComb, x1, x2) && sum_comb_calc(currComb, y1, y2)) (*unFrstCond)++;
        if (!sum_comb_calc(currComb, y1, y2)) (*unScndCondOnly)++;
        return;
    }

    for (i = start; i <= end && end-i+1 >= COMBSN-index; i++) 
    { 
        *(currComb + index) = *(arr + i);
		combinations(arr, currComb, freqArr, i+1, end, index+1, printed, unFrstCond, unScndCondOnly, x1, x2, y1, y2, N); 
    }
	
}


bool even_calc(int *arr, int x1, int x2)
{
    int numEven = 0, i;

    for (i = 0; i < COMBSN; i++)
        if (*(arr + i) % 2 == 0) numEven++;

    return (numEven >= x1 && numEven <= x2) ? true : false;
}


bool sum_comb_calc(int *arr, int y1, int y2)
{
    int sumNums = 0, i;

    for (i = 0; i < COMBSN; i++)
        sumNums += *(arr + i);
    
    return (sumNums >= y1 && sumNums <= y2) ? true : false;
}


void frequency(int *freqArr, int *currComb, int *arr, int N)
{
	int pos, i;

	for (i = 0; i < COMBSN; i++)
	{
		pos = find_pos(arr, N, *(currComb + i));
		(*(freqArr + pos))++;
	}
}


long int combinations_count(int N)
{
    return (factorial(N) / (factorial(COMBSN) * factorial(N - COMBSN)));
}


long double factorial(int num)
{
    int i;
    long double fac;
    if (num == 0) return -1;
    else for (i = 1, fac = 1; i <= num; i++) fac *= i;
    return fac;
}


void print_other(int N, int unFrstCond, int unScndCondOnly, int printed,int *arr, int *freqArr)
{
    int i;
	
	printf("\nTotal number of combinations %d to %d: %ld\n", N, COMBSN, combinations_count(N));
    printf("Number of combinations not satisfying the first condition: %d\n", unFrstCond);
    printf("Number of combinations not satisfying the second condition only: %d\n", unScndCondOnly);
    printf("Printed combinations: %d\n\n", printed);

	for (i = 0; i < N; i++)
		printf("%d appeared %d times\n", *(arr + i), *(freqArr + i));

}
