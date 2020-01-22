# Assignment 1.5: Arrays - Pointers - Files

**UNDER CONSTRUCTION, THE PROGRAMS DON'T WORK WELL YET**

## Programs

* combinations
* kcombinations
* fcombinations
* minesweeper

## Minesweeper

![MinesweeperScr](https://user-images.githubusercontent.com/54286563/72887644-cad7c500-3d14-11ea-8b8b-7e91df4806ab.png)

### How to play

* Enter number of columns
* Enter number of rows
* Enter number of mines
* Move with `w`/`s`/`a`/`d` or Vim keys (`k`/`j`/`h`/`l`)
* Open cell with `[ENTER]` or `o`
* Flag cell with `f`
* Defuse mine (if flagged) with `g`
* Quit with `q`

## Execution

* ```program_name``` = program's name
* ```full_path/``` = full path

### Linux

```shell
$ cd full_path/assignment-1.5-arrays-pointers-files/program_name
$ make
$ make run
$ make clean # optional
```

### Windows (not tested)

**Dependencies:**   
* MinGW gcc compiler
* ```make```

In CMD, do the following:

```bat
cd full_path/assignment-1.5-arrays-pointers-files/program_name
make
make run
make clean
```