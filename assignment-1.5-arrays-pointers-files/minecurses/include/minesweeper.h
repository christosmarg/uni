#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#if defined linux || defined __unix__ || defined __APPLE__
#include <ncurses.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "settings.h"
#include "gameplay.h"
#include "navigation.h"
#include "outputs.h"
#include "wins.h"
#include "audio.h"

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

char **init_dispboard(struct _win_st*, int, int);
void fill_dispboard(char **, int, int);
char **init_mineboard(struct _win_st*, int, int, int);

void place_mines(char **, int, int, int);
void add_adj(char **, int, int);
bool is_mine(char **, int, int);
bool outof_bounds(int, int, int, int);
int8_t adj_mines(char **, int, int, int, int);
void fill_spaces(char **, int, int, int);

#endif
