#include "fcombinations.h"

int main(int argc, char **argv)
{
    int *arr, N, x1, x2, y1, y2;
    FILE *dataFile = fopen(*(argv + 1), "r");

    if (dataFile == NULL)
    {
        set_color(BOLD_RED);
        printf("Error! Not enough memory, exiting...\n");
        exit(EXIT_FAILURE);
        set_color(STANDARD);
    }
    else
    {
        N = get_n(dataFile);
        arr = fill_array(N, dataFile);
        quicksort(arr, 0, N-1);
        x_pair(&x1, &x2, dataFile);
        y_pair(&y1, &y2, dataFile);
        print_combs(arr, N, x1, x2, y1, y2);
    }

    fclose(dataFile);
    free(arr);
   
    return 0;
}
