#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "minesweeper.h"

void play_minesweeper(struct _win_st*, char **, char **, int, int, int);
bool open_cell(struct _win_st*, char **, char **, int, int, bool);
void handle_flags(struct _win_st*, char **, char **, int, int);
void defuse_mine(struct _win_st*, char **, char **, int, int);
void transfer(char **, char **, int, int);
void reveal(struct _win_st*, char **, int, int, int, int);
bool is_defused(char **, char **, int, int);
void handle_gameover(struct _win_st*, char **, int, int, int, int, int, int);
void handle_win(struct _win_st*, char **, int, int, int, int, int, int, int);

#endif
