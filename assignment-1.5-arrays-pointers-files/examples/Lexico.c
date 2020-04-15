#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetSize (void);
void ClearBuf (void);
void RemoveEnter (char *);
char **ReadWords (int);
void PrintWords (char **, int);
void FreeMem (char **, int);
void SortWords (char **, int);
void SortWordsByLength (char **, short int *, int);
short int *CreateLexeisSize (char **, int);
void ShowMemory (char **, int);

int main (int argc, char **argv)
{
    char **Lexeis;
    short int *LexeisSize;
    int N;
    N = GetSize ();
    Lexeis = ReadWords (N);
    PrintWords (Lexeis, N);
    SortWords (Lexeis, N);
    PrintWords (Lexeis, N);
    LexeisSize = CreateLexeisSize (Lexeis, N);
    SortWordsByLength (Lexeis, LexeisSize, N);
    PrintWords (Lexeis, N);
    ShowMemory (Lexeis, N);
    FreeMem (Lexeis, N);
    
}

int GetSize ()
{
    int S;
    do
    {
        printf ("Enter Number of Words: ");
        scanf ("%d", &S);
    }
    while (S < 1);
    ClearBuf ();
    return S;
}

void ClearBuf ()
{
    char ch;
    while (( ch = getc (stdin)) != '\n' && ch != EOF);
}

void RemoveEnter (char *W)
{
    int i;
    for (i = 0; W[i] != 10 && W[i] != 13; i++);
    W[i] = 0;
}

char **ReadWords (int S)
{
    char **Words;
    char *Buf;
    int i;
    Buf = (char *) malloc (201);
    Words = (char **) malloc (S * sizeof (char *));
    for (i = 0; i < S; i++)
    {
        printf ("Enter word %d: ", i + 1);
        fgets (Buf, 201, stdin);
        RemoveEnter (Buf);
        Words[i] = (char *) malloc (strlen (Buf) + 1);
        strcpy (Words[i], Buf);
    }
    free (Buf);
    return Words;
}

void PrintWords (char **Words, int NoW)
{
    int i;
    printf ("  AA    Word                             Length\n");         
    for (i = 0; i < NoW; i++)
        printf ("[%3d]   %-30s   (%2d)\n", i + 1, Words[i], strlen (Words[i]));
    printf ("----------------------------------------------------------------------------------\n\n");
}

void FreeMem (char **L, int N)
{
    int i;
    for (i = 0; i < N; i++)
        free (*(L + i));
    free (L);
}

void SortWords (char **Words, int S)
{
    char *tmp;
    int i, j;
    for (i = 0; i < S - 1; i++)
        for (j = i + 1; j < S; j++)
            if (strcmp (Words[i], Words[j]) > 0)
            {
                tmp = Words[i];
                Words[i] = Words[j];
                Words[j] = tmp;
            }
}

void SortWordsByLength (char **Words, short int *WL, int S)
{
    short int tmp;
    char *tmp1;
    int i, j;
    for (i = 0; i < S - 1; i++)
        for (j = i + 1; j < S; j++)
            if (WL[i] > WL[j])
            {
                tmp = WL[i];
                WL[i] = WL[j];
                WL[j] = tmp;
                tmp1 = Words[i];
                Words[i] = Words[j];
                Words[j] = tmp1;
            }
}

short int *CreateLexeisSize (char **Words, int S)
{
    short int *Mat;
    int i;
    Mat = (short int *) malloc (S * sizeof (short int));
    for (i = 0; i < S; i++)
        *(Mat + i) = strlen (*(Words + i));
    return Mat;
}

void ShowMemory (char **W, int P)
{
    int i;
    printf ("The Lexeis pointer Contains: %p\n", W);
    printf ("  Lexeis+i      Lexeis[i]          Word\n");
    printf ("             --------------\n");
    for (i = 0; i < P; i++)
    {
        printf ("  %10p | %10p | ---> %s\n", W + i, *(W + i), *(W + i));
        printf ("             --------------\n");
    }
}
