#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "main.h"
#include <string.h>

#define SESSION_PATH "log/session.txt"
#define SCORE_LOG_PATH "log/scorelog.csv"

void print_board	(struct _win_st* gamew, Board *brd);
void print_grid		(struct _win_st* gamew, int rows, int cols);
void session_info	(int mbx, int mby, int xmid, int ndefused, int nmines);
void session_write	(Board *brd, int hitrow, int hitcol, const char *status);
void score_write	(int ndefused, int cols, int rows);
char *get_pname		(void);
void sort_scorelog	(FILE *scorelog);
void show_scorelog	(FILE *scorelog);
void parse_data		(FILE *scorelog);
void game_won		(struct _win_st* gamew, int ymid, int xmid);
void game_over		(struct _win_st* gamew, int ymid, int xmid);

#endif /* OUTPUTS_H */
