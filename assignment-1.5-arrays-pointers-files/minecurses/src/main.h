#ifndef MAIN_H
#define MAIN_H

#if defined linux || defined __unix__ || defined __APPLE__
#include <ncurses.h>
#endif

#include <stdlib.h>

#define YMAX getmaxy(stdscr)
#define XMAX getmaxx(stdscr)

typedef struct
{
	char **db;
	char **mb;
	int rows, cols, nmines;
} Board;

void reset(Board *brd);
void init_game(WINDOW *gamew, Board *brd);
void clear_board(Board *brd);

#endif /* MAIN_H */
