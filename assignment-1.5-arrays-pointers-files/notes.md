* quick sort
* seperate comb sources (file & manual)
* write to file minesweeper
* multiple txt (and 49 nums)
* 6 for
* meter function
* kcombinations
* combinations all in one with menu (6, k, file)
* < >
* ```c
void comb(int a[], int N)
{
    int i, j, k, l, m, n;
    
    for (i=0; i<N-5; i++)
        for (j=i+1; j<N-4; j++)
            for (k=j+1; k<N-3; k++)
                for (l=k+1; l<N-2; l++)
                    for (m=l+1; m<N-1; m++)
                        for (n=m+1; n<N; n++)
                        {
                            printf("%d %d %d %d %d %d", a[i], a[j], a[k], a[l], a[m], a[n]);
                            printf("\n");
                        }
}
```