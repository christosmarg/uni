#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "minesweeper.h"

void navigate	(struct _win_st* gamew, char *move, int *mbx, int *mby);
void getmv		(struct _win_st* gamew, char *move, int *y, int *x, int ymax, int xmax);
void mvup		(int *y);
void mvdown		(int *y, int ymax);
void mvleft		(int *x);
void mvright	(int *x, int xmax);
void update_curs(struct _win_st* gamew, int y, int x);

#endif /* NAVIGATION_H */
