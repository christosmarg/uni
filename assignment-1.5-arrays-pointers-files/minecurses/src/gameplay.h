#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "minesweeper.h"

void play_minesweeper	(struct _win_st* gamew, char **dboard, char **mboard, int COLS, int ROWS, int NMINES);
int open_cell			(struct _win_st* gamew, char **dboard, char **mboard, int mby, int mbx, int gameover);
void handle_flags		(struct _win_st* gamew, char **dboard, char **mboard, int mby, int mbx);
void defuse_mine		(struct _win_st* gamew, char **dboard, char **mboard, int mby, int mbx);
void transfer			(char **dboard, char **mboard, int mby, int mbx);
void reveal				(struct _win_st* gamew, char **dboard, int mby, int mbx, int y, int x);
int is_defused			(char **dboard, char **mboard, int mby, int mbx);
void handle_menu		(struct _win_st*, char **dboard, int COLS, int ROWS);
void handle_gameover	(struct _win_st* gamew, char **mboard, int ymid, int xmid, int COLS, int ROWS, int mby, int mbx);
void handle_win			(struct _win_st* gamew, char **mboard, int ymid, int xmid, int COLS, int ROWS, int mby, int mbx, int ndefused);

#endif /* GAMEPLAY_H */