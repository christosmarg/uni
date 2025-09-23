#ifndef MAIN_H
#define MAIN_H

#if defined linux || defined __unix__ || defined __APPLE__
#include <ncurses.h>
#endif /* defined linux || defined __unix__ || defined __APPLE__ */
#include <stdlib.h>

#define YMAX(x) getmaxy(x)
#define XMAX(x) getmaxx(x)

typedef struct {
	char **db;
	char **mb;
	int rows, cols;
	int nmines, ndefused;
	int gameover;
	int x, y;
	WINDOW *gw;
} Board;

extern Board b;

void reset		(Board *b);
void init_game	(Board *b);
void clear_board(Board *b);

#endif /* MAIN_H */
