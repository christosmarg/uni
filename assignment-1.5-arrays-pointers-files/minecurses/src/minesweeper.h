#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "wins.h"

#define BLANK ' '
#define MINE '*'

void init_db	 (struct _win_st* gw, Board *b);
void fill_db	 (Board *b);
void init_mb	 (struct _win_st* gw, Board *b);
void place_mines (Board *b);
void add_adj	 (Board *b);
int is_mine		 (Board *b, int row, int col);
int outof_bounds (Board *b, int row, int col);
uint8_t adj_mines(Board *b, int row, int col);
void fill_spaces (Board *b);

#endif /* MINESWEEPER_H */
