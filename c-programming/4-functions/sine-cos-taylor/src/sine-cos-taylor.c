#include <stdio.h>
#include <math.h>
#include "sine-cos-taylor.h"

#define PI 3.141592654
#define ACCURACY 0.000001
#define COMPARISON 0.000009

double input()
{
    double xDegrees;
    
    printf("x (in degrees): ");
    scanf("%lf", &xDegrees);

    return xDegrees;
}

double rads_conv(double xDegrees)
{
    return xDegrees * (PI/180.0);
}

double sine_calc(double xRads)
{
    double currentFrac, previousFrac, sineValue = 0;
    int exponent = 1, sign = 1;
    
    currentFrac = power(xRads, exponent) / factorial(exponent);
    
    do
    {        
        sineValue += sign * currentFrac;
    
        exponent += 2;

        previousFrac = currentFrac;
        currentFrac = power(xRads, exponent) / factorial(exponent);
        
        sign *= -1;
    } while (fabs(previousFrac - currentFrac) > ACCURACY);

    return sineValue;
}

double cosine_calc(double xRads)
{
    double currentFrac = 1, previousFrac, cosineValue = 0;
    int exponent = 0, sign = 1;
    
    do
    {        
        cosineValue += sign * currentFrac;
    
        exponent += 2;

        previousFrac = currentFrac;
        currentFrac = power(xRads, exponent) / factorial(exponent);
        
        sign *= -1;
    } while (fabs(previousFrac - currentFrac) > ACCURACY);

    return cosineValue;
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

int compare(double calcValue, double funcValue)
{
    if (fabs(calcValue - funcValue) <= COMPARISON)
        return 1;
    else
        return 0;
}