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

#endif
