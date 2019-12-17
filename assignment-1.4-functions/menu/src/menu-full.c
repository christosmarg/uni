#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void menu(int, int);
void pause();
void results(int, int, int);
int power(int, int);
int factorial(int);
int combinations(int, int);


int main(int argc, char **argv)
{
    int a, b;

    printf("A: ");
    scanf("%d", &a);
    printf("B: ");
    scanf("%d", &b);
    
    menu(a, b);

    return 0;
}


void menu(int a, int b)
{
    int menuChoice;

    do
    {
        system("clear||cls");

        printf("[1] %d to the power of %d\n[2] %d! and %d!\n[3] Number of combinations between %d and %d\n[4] Exit\n", a, b, a, b, a, b);
        printf("Choice: ");
        scanf(" %d", &menuChoice);

        switch(menuChoice)
        {
            case 1:
                results(a, b, 1);
                break;
            case 2:
                results(a, b, 2);
                break;
            case 3:
                results(a, b, 3);
                break;
        }
        
        pause();
    } while (menuChoice != 4);

    results(a, b, 4);
}

void pause()
{
    do
    {
        printf("\nPress [Enter] to continue. . .");
        getchar();
    } while (getchar() != '\n');
    
}

void results(int a, int b, int menuChoice)
{
    static int numChoices = 0;
    
    switch(menuChoice)
    {
        case 1:
            printf("%d^%d = %d\n", a, b, power(a, b));
            break;
        case 2:
            printf("%d! = %d\n", a, factorial(a));
            printf("%d! = %d\n", b, factorial(b));
            break;
        case 3:
            printf("Combinations between %d and %d: %d\n", a, b, combinations(a, b));
            break;
        case 4:
            printf("Total number of choices: %d\n", numChoices);
    }

    numChoices++;
}

int power(int a, int b)
{
    return pow(a, b);
}

int factorial(int num)
{
    int i, fac;

    for (i = 1, fac = 1; i <= num; i++)
        fac *= i;

    return fac;
}

int combinations(int a, int b)
{
    return factorial(b) / (factorial (a) * factorial(abs(b-a)));
}