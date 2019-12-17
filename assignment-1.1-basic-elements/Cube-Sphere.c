#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    double length, rad, area_cube, vol_cube, area_sphere, vol_sphere;
    const double PI = 3.14;

    printf("Μήκος (σε μέτρα): ");
    scanf("%lf", &length);

    area_cube = 6.0*pow(length, 2);
    vol_cube = pow(length, 3);
    rad = length;
    area_sphere = 4.0*PI*pow(rad, 2);
    vol_sphere = (4.0/3.0)*PI*pow(rad, 3);

    printf("Εμβαδόν κύβου: %.2lf\n", area_cube);
    printf("Όγκος Κύβου: %.2lf\n\n", vol_cube);
    printf("Εμβαδόν σφαίρας: %.2lf\n", area_sphere);
    printf("Όγκος σφαίρας: %.2lf\n", vol_sphere);
    
    return 0;
}