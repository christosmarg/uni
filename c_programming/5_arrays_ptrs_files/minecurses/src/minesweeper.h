#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "wins.h"

#define BLANK ' '
#define MINE '*'

void init_db	 (Board *b);
void fill_db	 (Board *b);
void init_mb	 (Board *b);
void place_mines (Board *b);
void add_adj	 (Board *b);
int is_mine		 (const Board *b, int r, int c);
int outof_bounds (const Board *b, int r, int c);
uint8_t adj_mines(const Board *b, int r, int c);
void fill_spaces (Board *b);
void die		 (void);

#endif /* MINESWEEPER_H */
