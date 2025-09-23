#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "minesweeper.h"

void navigate(struct _win_st*, char **, char *, int *, int *);
void getmv(struct _win_st*, char *, int *, int *, int, int);
void mvup(int *);
void mvdown(int *, int);
void mvleft(int *);
void mvright(int *, int);
void update_curs(struct _win_st*, int, int);

#endif