#include <stdio.h>

void moves(int, char, char, char);

int main(int argc, char **argv)
{
    int numDisks;

    printf("\t\tTower of Hanoi\n\n");

    do
    {
        printf("Number of disks: ");
        scanf("%d", &numDisks);
    } while (numDisks <= 0);
    
    printf("\n");
    moves(numDisks, 'A', 'B', 'C');

    return 0;
}

void moves(int numDisks, char tower1, char tower2, char tower3)
{
    if (numDisks == 1)
        printf("Move disk 1 from tower %c to tower %c\n", tower1, tower3);
    else
    {
        moves(numDisks - 1, tower1, tower3, tower2);
        printf("Move disk %d from tower %c to tower %c\n", numDisks, tower1, tower3);
        moves(numDisks - 1, tower2, tower1, tower3);
    } 
}