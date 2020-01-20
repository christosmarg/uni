#include "kcombinations.h"

int main(int argc, char **argv)
{
    int *arr, N, K, x1, x2, y1, y2;

    N = get_n();
    K = get_k(N);

    arr = fill_array(N);
    quicksort(arr, 0, N-1);
    x_pair(&x1, &x2);
    y_pair(&y1, &y2);
    print_combs(arr, N, K, x1, x2, y1, y2);

    free(arr);

    return 0;
}