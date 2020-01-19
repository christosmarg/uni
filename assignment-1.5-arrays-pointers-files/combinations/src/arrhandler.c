#include <stdio.h>
#include <stdlib.h>
#include "arrhandler.h"
#include "combinations.h"
#include "ccolors.h"


int *fill_array(int N)
{
    int num, i = 0;
    int *arr = (int *)malloc(N * sizeof(int));

    if (arr == NULL)
    {
        set_color(BOLD_RED);
        printf("Error! Not enough memory, exiting...\n");
        exit(EXIT_FAILURE);
        set_color(STANDARD);
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
    int *arrEnd = arr + (N - 1);
    while (arr <= arrEnd && *arr != num) arr++;
    return (arr <= arrEnd) ? true : false;
}


void quicksort(int *arr, int low, int high)
{
    if (low < high) 
    { 
        int partIndex = partition(arr, low, high); 
        quicksort(arr, low, partIndex - 1); 
        quicksort(arr, partIndex + 1, high);
    }
}


int partition(int *arr, int low, int high)
{
    int pivot = *(arr + high);
    int i = (low - 1), j;
  
    for (j = low; j <= high - 1; j++) 
        if (*(arr + j) < pivot) 
            swap(arr + ++i, arr + j); 

    swap(arr + (i + 1), arr + high); 
    return (i + 1); 
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}