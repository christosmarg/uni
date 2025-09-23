#ifndef WINS_H
#define WINS_H

#include "minesweeper.h"

void main_win();
WINDOW *menu_win(int *, int *);
WINDOW *game_win(int, int, int);
void options_menu();
void options_win();

#endif
