#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "minesweeper.h"

void play_minesweeper(struct _win_st*, char **, char **, int, int, int);
void transfer(char **, char **, int, int, int, int *);
void reveal(struct _win_st*, char **, int, int, int, int);
void flag_handler();
bool is_flagged();
bool is_defused(char **, char **, int, int);

#endif