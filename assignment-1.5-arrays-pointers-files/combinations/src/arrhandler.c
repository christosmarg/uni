#include <stdlib.h>
#include "arrhandler.h"
#include "ccolors.h"

#define COMBSN 6


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


void printarray(int *arr, int N)
{
    for (int i = 0; i < N; i++)
        printf("arr[%d] = %d\n", i, *(arr + i));
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