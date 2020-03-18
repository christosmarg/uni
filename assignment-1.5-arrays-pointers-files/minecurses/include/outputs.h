#ifndef OUTPUTS_H
#define OUTPUTS_H

#include "minesweeper.h"

#define SESSION_PATH "txt/mnsout.txt"
#define SCORE_LOG_PATH "txt/scorelog.txt"

void print_grid(struct _win_st*, int, int);
void print_board(struct _win_st*, char **, int, int);
void game_won(struct _win_st*, int, int);
void game_over(struct _win_st*, char **, int, int);
void session_write(char **, int, int, int, int, const char *);
void score_write(int, int, int);
char *get_pname();
void sort_scorelog(FILE *);

#endif
