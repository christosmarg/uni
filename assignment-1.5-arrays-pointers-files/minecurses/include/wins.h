#ifndef WINS_H
#define WINS_H

#include "minesweeper.h"

void init_curses	(void);
WINDOW *game_win	(int COLS, int ROWS, int NMINES);
void options_menu	(void);
void fill_menu		(struct _win_st*);

#endif /* WINS_H */
