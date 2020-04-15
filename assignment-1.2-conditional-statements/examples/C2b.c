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
    if (a > b)
        if (a > c)
            printf("Ο μεγαλύτερος είναι ο %d και εισήχθη 1ος\n", a);
        else
            if (a == c)
                printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 1ος και 3ος\n", a);
            else
                printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 3ος\n", c);
    else
        if (a == b)
            if (a == c)
                printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 1ος, 2ος και 3ος\n", a);
            else
                if (a > c)
                    printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 1ος και 2ος\n", a);
                else
                    printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 3ος\n", c);
        else
            if (b > c)
                printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 2ος\n", b);
            else
                if (b == c)
                    printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 2ος και 3ος\n", a);
                else
                    printf ("Ο μεγαλύτερος είναι ο %d και εισήχθη 3ος\n", c);
    return 32;
}
