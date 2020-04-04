#ifndef WINS_H
#define WINS_H

#include "minesweeper.h"

void main_win		(void);
WINDOW *menu_win	(int *ymax, int *xmax);
WINDOW *game_win	(int COLS, int ROWS, int NMINES);
void options_menu	(void);
void options_win	(void);

#endif /* WINS_H */
