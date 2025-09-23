# Assignment 1.5: Arrays - Pointers - Files

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
* Defuse mine (only if flagged) with `g`
* You win if you defuse all the mines
* You lose in case you open a mine or you try to defuse a flagged cell not containing a mine
* Quit with `q`

### To Do

* Fix screen bug with big dimensions
* Add colors

## Combinations / KCombinations / FCombinations

Combination printing programs

## Execution

* `program_name` = program's name
* `full_path/` = full path

### Linux

**Dependencies**
* `ncurses`

```shell
$ cd full_path/assignment-1.5-arrays-pointers-files/program_name
$ make
$ make run
$ make clean # optional
```

### Windows (not tested)

**Dependencies:**   
* MinGW gcc compiler
* `make`
* `PDCurses` library (for minesweeper)

In CMD, do the following:

```bat
cd full_path/assignment-1.5-arrays-pointers-files/program_name
make
make run
make clean
```