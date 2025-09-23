#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "minesweeper.h"

#define SESSION_PATH "txt/mnsout.txt"
#define SCORE_LOG_PATH "txt/scorelog.txt"

void print_board	(struct _win_st* gamew, char **dboard, int COLS, int ROWS);
void print_grid		(struct _win_st* gamew, int ROWS, int COLS);
void session_write	(char **mboard, int COLS, int ROWS, int hitrow, int hitcol, const char *status);
void score_write	(int ndefused, int COLS, int ROWS);
char *get_pname		(void);
void sort_scorelog	(FILE *scorelog);
void game_won		(struct _win_st* gamew, int ymid, int xmid);
void game_over		(struct _win_st* gamew, char **mboard, int ymid, int xmid);

#endif /* OUTPUTS_H */
