#include <stdio.h>

int main (int NoP, char **Params)
{
    int a, b, c;
    int Max;
    printf ("ΕΥΡΕΣΗ ΜΕΓΙΣΤΟΥ ΑΡΙΘΜΟΥ\n\n");
    printf ("Εισάγετε τον πρώτο αριθμό   : ");
    scanf ("%d", &a);
    printf ("Εισάγετε τον δεύτερο αριθμό : ");
    scanf ("%d", &b);
    printf ("Εισάγετε τον τρίτο αριθμό   : ");
    scanf ("%d", &c);
    Max = a;
    if (b > Max)
        Max = b;
    Max = (c > Max)? c: Max;
    printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη:\n", Max);
    if (Max == a) 
        printf("  1ος\n");
    if (Max == b)
        printf("  2ος\n");
    if (Max == c)
        printf("  3ος\n");
    return 124;
}
