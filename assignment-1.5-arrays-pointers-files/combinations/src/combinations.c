#include <stdio.h>


int define_size();
void fill_array(int);
int exists_in_array(int*, int, int);
void pairs();


int main(int argc, char *argv[])
{
    int N = define_size();

    fill_array(N);
    pairs();

    return 0;
}



int define_size()
{
    int N;
    
    do
    {
        printf("N: ");
        scanf("%d", &N);
    } while (N <= 6 || N > 49);

    return N;
}



void fill_array(int N)
{
    int i = 0, num, arr[N];

    do
    {
        printf("arr[%d]: ", i);
        scanf("%d", &num);

        if (num >= 1 && num <= 49)
        {
            if (i == 0)
            {
                arr[i] = num;
                i++;
            }
            else
            {
                if (!exists_in_array(arr, N, num))
                {
                    arr[i] = num;
                    i++;
                }
                else
                    printf("Give a different number.\n");
            }
        }
        else
            printf("Give a number in [1, 49].\n");
            
    } while (i < N);
}



int exists_in_array(int *arr, int N, int num)
{
    int *arrEnd = arr + N - 1;

    while (arr <= arrEnd && *arr != num)
        arr++;
    
    if (arr <= arrEnd)
        return 1;
    else
        return 0;
}



void pairs()
{
    int x1, x2, y1, y2;

    do
    {
        printf("x1: ");
        scanf("%d", &x1);

        printf("x2: ");
        scanf("%d", &x2);

    } while (x1 < 0 || x1 > x2 || x2 > 6);

    do
    {
        printf("y1: ");
        scanf("%d", &y1);

        printf("y2: ");
        scanf("%d", &y2);

    } while (y1 < 21 || y1 > y2 || y2 > 279);
            
}