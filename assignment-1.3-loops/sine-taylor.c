#include <stdio.h>
#include <math.h>

#define PI 3.141592654
#define ACCURACY 0.000001

double power(double, int);
double factorial(int);


int main(int argc, char *argv[])
{
    double xDegrees, xRads, currentFrac, previousFrac, sine = 0;
    int exponent = 1, sign = 1;

    printf("x (in degrees): ");
    scanf("%lf", &xDegrees);
    xRads = xDegrees * (PI/180.0);
    
    currentFrac = power(xRads, exponent) / factorial(exponent);
    
    do
    {        
        sine += sign * currentFrac;
    
        exponent += 2;

        previousFrac = currentFrac;
        currentFrac = power(xRads, exponent) / factorial(exponent);
        
        sign *= -1;
    }
    while (fabs(previousFrac - currentFrac) > ACCURACY);

    printf("sin(%lf) = sin(%lf) = %lf rads\n", xDegrees, xRads, sine);

    return 0;
}


double power(double xRads, int exponent)
{
    int i;
    double value;

    for (i = 0, value = 1; i < exponent; i++)
        value *= xRads;

    return value;
}


double factorial(int exponent)
{
    int i;
    double fac;

    for (i = 1, fac = 1; i <= exponent; i++)
        fac *= i;

    return fac;
}