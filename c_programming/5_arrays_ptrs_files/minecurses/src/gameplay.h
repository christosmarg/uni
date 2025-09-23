#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "audio.h"
#include "main.h"
#include "navigation.h"
#include "outputs.h"
#include "wins.h"

#define BLANK ' '
#define MINE '*'
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

void play			(Board *b);
int open_cell		(Board *b);
void handle_flags	(Board *b);
void defuse_mine	(Board *b);
void transfer		(Board *b);
void reveal			(const Board *b);
int is_defused		(const Board *b);
void handle_menu	(const Board *b);
void handle_gameover(const Board *b);
void handle_win		(const Board *b);

#endif /* GAMEPLAY_H */
