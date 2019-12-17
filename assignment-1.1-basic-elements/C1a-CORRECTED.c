#include <stdio.h>

int main(int argc, char **argv)
{
    int A, B;
    int C, D, E, F; 
    system ("chcp 1253");
    printf ("Βασικές αριθμητικές πράξεις με Ακεραίους\n");
    printf ("========================================\n\n");
    printf ("Εισάγετε τον πρώτο αριθμό  : ");
    scanf ("%d",&A);
    printf ("Εισαγετε το δεύτερο αριθμό : ");
    scanf ("%d", &B);
    C = A + B;
    D = A - B;
    E = A * B;
    F = A / B;
    printf ("Άθροισμα  : %d\n", C);
    printf ("Διαφορά   : %d\n", D);
    printf ("Γινόμενο  : %d\n", E);
    printf ("Πηλίκο    : %d\n", F);
    return 0;
}