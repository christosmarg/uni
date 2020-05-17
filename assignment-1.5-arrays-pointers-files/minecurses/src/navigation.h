#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "main.h"
#include "minesweeper.h"

void navigate	(struct _win_st* gw, int *mv, int *mbx, int *mby);
void getmv		(struct _win_st* gw, int *mv, int *y, int *x);
void mvup		(int *y);
void mvdown		(int *y, int xmax);
void mvleft		(int *x);
void mvright	(int *x, int xmax);
void update_curs(struct _win_st* gw, int y, int x);

#endif /* NAVIGATION_H */
