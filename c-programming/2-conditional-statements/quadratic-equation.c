#include <stdio.h>
#include <math.h>


void linearEquation();
void quadraticEquation();


int main(int argc, char **argv)
{
    double a, b, c; 

    printf("a: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);
    printf("c: ");
    scanf("%lf", &c);

    if (a != 0)
        quadraticEquation(a, b, c);
    else
        linearEquation(b, c);
    
    return 0;
}


void linearEquation(double b, double c)
{
    double x;

    if (b != 0)
    {
        x = -c / b;
        printf("x = %.2lf\n", x);
    }
    else
        printf("Infinite solutions.\n");
}


void quadraticEquation(double a, double b, double c)
{
    double x, x1, x2, D = pow(b, 2) - 4*(a*c);

    if (D > 0)
    {
        x1 = (-b + sqrt(D)) / (2*a);
        x2 = (-b - sqrt(D)) / (2*a);
        printf("x1 = %.2lf\nx2 = %.2lf\n", x1, x2);
    }
    else if (D == 0)
    {
        x = (-b) / (2*a);
        printf("x = %.2lf\n", x);
    }
    else
    {
        printf("There are no solutions.\n");
    }
}