# minescurses

A minesweeper game using the `ncurses` and `SDL2` libraries. The game was originally made as a university assignment of mine, but I decided to take it a bit further afterwards.

## How to play

* Enter number of columns
* Enter number of rows
* Enter number of mines
* Move with `w`/`s`/`a`/`d` or Vim keys (`k`/`j`/`h`/`l`)
* Open cell with `[ENTER]`, or `o`
* Flag cell with `f`
* Defuse mine (only if flagged) with `g`
* You win if you defuse all the mines
* You lose in case you open a mine or you try to defuse a flagged cell not containing a mine

Additional controls

* `p`: Pause audio
* `+`: Volume up
* `-`: Volume down
* `q`: Quit

## To Do

* Handle resizing
* Add restart option
* Add quit option right when game opens
* Load score log to ui
* Improve score log
* Add macros for the scaled board dimensions
* Add colors
* Fix curs_set
* Add echo during setup
* Add unicode support

## Execution

### Linux / Unix / macOS

**Dependencies**
* `make`
* `ncurses`
* `SDL2`
* `SDL2_mixer`

```shell
$ cd path_to/minecurses
$ make
$ make run
$ make clean # optional
```

## Preview

![MinesweeperScr](https://user-images.githubusercontent.com/54286563/73931645-4d4db080-48e1-11ea-981b-e9b028d34c41.png)
