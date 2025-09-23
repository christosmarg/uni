#include "combinations.h"

int main(int argc, char **argv)
{
    int *arr, N, x1, x2, y1, y2;

    N = get_n();

    arr = fill_array(N);
    quicksort(arr, 0, N-1);
    x_pair(&x1, &x2);
    y_pair(&y1, &y2);
    print_combs(arr, N, x1, x2, y1, y2);

    free(arr);

    return 0;
}