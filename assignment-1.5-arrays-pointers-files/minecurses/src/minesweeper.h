#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "wins.h"

#define BLANK ' '
#define MINE '*'

char **init_db		(struct _win_st* gamew, int cols, int rows);
void fill_db		(char **db, int cols, int rows);
char **init_mb		(struct _win_st* gamew, int cols, int rows, int nmines);
void place_mines	(char **mb, int cols, int rows, int nmines);
void add_adj		(char **mb, int cols, int rows);
int is_mine			(char **mb, int row, int col);
int outof_bounds	(int row, int col, int rows, int cols);
uint8_t adj_mines	(char **mb, int row, int col, int cols, int rows);
void fill_spaces	(char **mb, int cols, int rows, int nmines);

#endif /* MINESWEEPER_H */
