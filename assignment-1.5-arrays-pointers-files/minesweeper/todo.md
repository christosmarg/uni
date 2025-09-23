* limits
* resizing
* ```selection()```
* ```transfer()```
* ```reveal()```
* ```is_mine()```
* ```game_over()```
* Game over menu
  * Press key to continue
  * Dialog menu

* Export to text

  * Get file name
  * Write to file

```c
pin = (char **)malloc(M*sizeof(char *));
for (int i = 0; i < M; i++)
    *(pin + i) = (char *)malloc(N);
```