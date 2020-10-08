#include <stdio.h>

int main(int argc, char *argv[])
{
    int row, rowsTotal, col, colsTotal, spaces;
    
    printf("How many rows?: ");
    scanf("%d", &rowsTotal);
    colsTotal = rowsTotal;

    printf("\n");
    
    for (row = 0; row < rowsTotal; row++)
    {
        printf("*\n");
        for (col = row+1; col > 0; col--)
        {
            if (row+1 < colsTotal)
                printf("*");
        }
    }

    printf("\n");

    for (row = 0; row < rowsTotal; row++)
    {
        for (col = row+1; col < colsTotal; col++)
            printf(" ");
        
        for (col = 0; col <= row; col++)
            printf("*");

        printf("\n");
    }

    printf("\n");

    spaces = rowsTotal;
    for (row = 1; row <= rowsTotal; row++)
    {
        for (col = 1; col < spaces; col++)
            printf(" ");
        
        for (col = 0; col < 2*row - 1; col++)
            printf("*");
        
        printf("\n");
        spaces--;
    }

    printf("\n");

    for (row = 1; row <= rowsTotal; row++)
    {
        for (col = 1; col <= colsTotal; col++)
        {
            if (row == 1 || row == rowsTotal || col == 1 || col == colsTotal)
                printf("*");                
            else if (row == col || col == (rowsTotal - row + 1))
                printf("·");
            else
                printf(" ");
        }

        printf("\n");
    }

    printf("\n");

    return 0;
}