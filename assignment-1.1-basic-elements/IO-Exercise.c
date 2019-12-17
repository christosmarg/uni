#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    int int_1, int_2, sum, diff, prod, div, sqr;
    double f_div, sqr_root;

    printf("Ακέραιος 1: ");
    scanf("%d", &int_1);
    printf("Ακέραιος 2: ");
    scanf("%d", &int_2);

    sum = int_1 + int_2;
    diff = int_1 - int_2;
    prod = int_1 * int_2;

    sqr = pow(int_1, 2);
    sqr_root = sqrt(int_2);

    printf("Άθροισμα: %d\n", sum);
    printf("Διαφορά: %d\n", diff);
    printf("Γινόμενο: %d\n", prod);
    printf("Τετράγωνο: %d\n", sqr);
    printf("Τετραγωνική ρίζα: %.2lf\n", sqr_root);
    if (int_2 != 0)
    {
        div = int_1 / int_2;
        f_div = (double)int_1 / int_2;
        printf("Πηλίκο: %d\n", div);
        printf("Πραγματικό πηλίκο: %.2lf\n", f_div);
    }
    else
    {
        printf("Δεν γίνεται διαίρεση με το 0.\n");
    }
    
    return 0;
}