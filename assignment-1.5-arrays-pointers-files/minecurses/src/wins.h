#ifndef WINS_H
#define WINS_H

#include "main.h"

void init_curses (void);
WINDOW *game_win (int rows, int cols);
void options_menu(void);
void fill_menu	 (struct _win_st* opts);

#endif /* WINS_H */
