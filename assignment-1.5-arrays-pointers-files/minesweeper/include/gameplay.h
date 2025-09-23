#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "minesweeper.h"

#define DEFUSEKEY 'd'

void selection(struct _win_st*, char **, char **, int, int, int);
bool transfer(char **, char **, int, int, int, int *);
void reveal(struct _win_st*, char **, int, int);
bool defused(char **, char **, int, int, int, int *);

#endif