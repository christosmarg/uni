#include <stdio.h>

int main(int argc, char *argv[])
{
    int num, averPos, sqrOdd;
    int sumPos = 0, numPos = 0, numEven = 0, prodNeg = 1;

    do
    {
        printf("Number: ");
        scanf("%d", &num);

        if (num > 0)
        {
            sumPos += num;
            numPos += 1;


            if (num % 2 != 0)
            {
                sqrOdd = num * num;
                printf("Square of odd number %d: %d\n", num, sqrOdd);
            }
            else
                numEven += 1;
        }
        else if (num < 0)
            prodNeg *= num;
    }
    while (num != 0);

    averPos = sumPos / numPos;

    printf("Average value of positive numbers: %d\n", averPos);
    printf("Product of negative numbers: %d\n", prodNeg);
    printf("Number of even numbers: %d\n", numEven);

    return 0;
}