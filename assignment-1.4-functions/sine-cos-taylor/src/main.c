#include <stdio.h>
#include <math.h>
#include "sine-cos-taylor.h"


int main(int argc, char **argv)
{
    double xDegrees, xRads;

    xDegrees = input();

    xRads = rads_conv(xDegrees);

    if (compare(sine_calc(xRads), sin(xRads)))
        printf("sin(%f) = sin(%f) = %f rads\n", xDegrees, xRads, sine_calc(xRads));
    else
        printf("Error.\n");

    if (compare(cosine_calc(xRads), cos(xRads)))
        printf("cos(%f) = cos(%f) = %f rads\n", xDegrees, xRads, cosine_calc(xRads));
    else
        printf("Error.\n");

    return 0;
}