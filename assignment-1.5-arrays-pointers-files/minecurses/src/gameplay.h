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

void play				(struct _win_st* gamew, Board *brd);
int open_cell			(struct _win_st* gamew, Board *brd, int mby, int mbx, int gameover);
void handle_flags		(struct _win_st* gamew, Board *brd, int mby, int mbx);
void defuse_mine		(struct _win_st* gamew, Board *brd, int mby, int mbx);
void transfer			(Board *brd, int mby, int mbx);
void reveal				(struct _win_st* gamew, Board *brd, int mby, int mbx, int y, int x);
int is_defused			(Board *brd, int mby, int mbx);
void handle_menu		(struct _win_st*, Board *brd);
void handle_gameover	(struct _win_st* gamew, Board *brd, int ymid, int xmid, int mby, int mbx);
void handle_win			(struct _win_st* gamew, Board *brd, int ymid, int xmid, int mby, int mbx, int ndefused);

#endif /* GAMEPLAY_H */
