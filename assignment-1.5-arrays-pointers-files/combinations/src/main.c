#include <stdio.h>
#include <stdlib.h>
#include "combinations.h"
#include "arrhandler.h"


int main(int argc, char **argv)
{
    int N, K;
    int *arr;
    int x1, x2, y1, y2;

    N = get_n();
    arr = fill_array(N);
    quicksort(arr, 0, N-1);
    //printarray(arr, N);
    
    x_pair(&x1, &x2);
    y_pair(&y1, &y2);

    combinations(arr, x1, x2, y1, y2);
    
    free(arr);

    return 0;
}