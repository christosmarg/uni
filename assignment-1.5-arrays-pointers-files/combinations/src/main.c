#include <stdio.h>
#include <stdlib.h>
#include "combinations.h"


int main(int argc, char **argv)
{
    int N, K;
    int *arr;
    int x1, x2, y1, y2;

    N = get_n("N");
    K = get_n("K");
    arr = fill_array(N);
    x_pair(&x1, &x2);
    y_pair(&y1, &y2);
    combinations(arr);

    
    free(arr);

    return 0;
}
