#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "wins.h"

#define BLANK ' '
#define MINE '*'

char **init_dboard	(struct _win_st* gamew, int cols, int rows);
void fill_dboard	(char **dboard, int cols, int rows);
char **init_mboard	(struct _win_st* gamew, int cols, int rows, int nmines);
void place_mines	(char **mboard, int cols, int rows, int nmines);
void add_adj		(char **mboard, int cols, int rows);
int is_mine			(char **mboard, int row, int col);
int outof_bounds	(int row, int col, int rows, int cols);
uint8_t adj_mines	(char **mboard, int row, int col, int cols, int rows);
void fill_spaces	(char **mboard, int cols, int rows, int nmines);

#endif /* MINESWEEPER_H */
