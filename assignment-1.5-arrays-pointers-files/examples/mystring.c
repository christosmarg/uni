#include <stdio.h>
#include <string.h>

int mystrcmp (char *, char *);
int mystrlen (char *);
void mystrcpy (char *, char *);
char *mystrcat (char *, char *);

int main (int argc, char **argv)
{
    char Str1[50] = "Thanasis";
    char Str2[50] = "Maria";
    char Str3[50] = "MariaP";
    char Str4[50] = "";
    
    printf ("Name 1 : %s\n", Str1);
    printf ("Name 2 : %s\n", Str2);
    printf ("Name 3 : %s\n", Str3);
    printf ("Name 4 : %s\n", Str4);
    
    printf ("\n");
    printf ("Compare Name 1 with Name 2: %d \n", mystrcmp (Str1, Str2));
    printf ("Compare Name 2 with Name 1: %d \n", mystrcmp (Str2, Str1));
    printf ("Compare Name 1 with Name 1: %d \n", mystrcmp (Str1, Str1));
    printf ("Compare Name 2 with Name 3: %d \n", mystrcmp (Str2, Str3));
    printf ("Compare Name 3 with Name 2: %d \n", mystrcmp (Str3, Str2));
    
    printf ("\n");
    printf ("Length of Name 1      : %d\n", mystrlen (Str1));
    printf ("Length of Name 2      : %d\n", mystrlen (Str2));
    printf ("Length of Null String : %d\n", mystrlen (""));
    
    printf ("\n");
    mystrcpy (Str4, Str1);
    printf ("Name 4: %s is copy of Name 1: %s\n", Str4, Str1);
    
    printf ("\n");
    mystrcat (Str4, Str2);
    printf ("New Name 4: %s\n", Str4);
    
    
}

/*
 * Υλοποίηση της "strcmp"
 * Αυτό που επιστρέφει είναι το ίδιο / συμβατό με αυτό που επιστρέφει η έτοιμη συνάρτηση;
 * Υλοποιείστε την strncmp
 */
 
int mystrcmp (char *s1, char *s2)
{
    int i;
    for (i = 0; s1[i] == s2[i] && s1[i] != 0; i++);
    return s1[i] - s2[i];
}

/*
 * Υλοποίηση της "strlen".
 * Ξεκαθαρείστε το νόημα της συνθήκης, συντακτικά και λογικά
 */ 
int mystrlen (char *s)
{
    int i;
    for (i = 0; s[i]; i++);
    return i;
}

/*
 * Υλοποίηση της "strcpy"
 * Είναι κατανοητό πως δουλεύει;
 * Σε τι διαφέρει από την έτοιμη συνάρτηση; Διορθώστε την ώστε να πληροί τις προδιαγραφές της έτοιμης συνάρτησης.
 * Υλοποιείστε την με έναν... πιο αλγοριθμικό τρόπο.
 * Υλοποιείστε την strncpy
 */
void mystrcpy (char *d, char *s)
{
    int i = 0;
    while (d[i]=s[i++]);
}

/*
 * Υλοποίηση της "strcat"
 * Υλοποιείστε την χωρίς την κλήση άλλης συνάρτησης.
 * Υλοποιείστε την strncat
 */ 
char *mystrcat (char *d, char *s)
{
    char *tmp;
    tmp = d;
    while (*tmp)
        tmp++;
    // while (*(tmp++));    // Γιατί όχι μόνο αυτό;
    mystrcpy (tmp, s);
    return d;
}

/*
 * Υλοποιείστε τις παρακάτω συναρτήσεις:
 * -strdup
 * -strlwr
 * -strupr
 */

