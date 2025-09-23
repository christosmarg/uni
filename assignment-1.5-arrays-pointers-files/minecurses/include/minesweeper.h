#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#if defined linux || defined __unix__ || defined __APPLE__
#include <ncurses.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "audio.h"
#include "gameplay.h"
#include "navigation.h"
#include "outputs.h"
#include "settings.h"
#include "wins.h"

#define BLANK ' '
#define MINE '*'
#define CLEAR "                               "
#define ENTER '\n'
#define OPEN_LOWER 'o'
#define OPEN_UPPER 'O'
#define FLAG 'F'
#define FLAG_LOWER 'f'
#define FLAG_UPPER 'F'
#define DEFUSE_LOWER 'g'
#define DEFUSE_UPPER 'G'
#define DEFUSED 'D'
#define PAUSE_AUDIO 'p'
#define VOLUME_UP '+'
#define VOLUME_DOWN '-'
#define QUIT 'q'

char **init_dboard	(struct _win_st* gamew, int COLS, int ROWS);
void fill_dboard	(char **dboard, int COLS, int ROWS);
char **init_mboard	(struct _win_st* gamew, int COLS, int ROWS, int NMINES);
void place_mines	(char **mboard, int COLS, int ROWS, int NMINES);
void add_adj		(char **mboard, int COLS, int ROWS);
int is_mine			(char **mboard, int row, int col);
int outof_bounds	(int row, int col, int ROWS, int COLS);
uint8_t adj_mines	(char **mboard, int row, int col, int COLS, int ROWS);
void fill_spaces	(char **mboard, int COLS, int ROWS, int NMINES);

#endif /* MINESWEEPER_H */
