#ifndef SETTINGS_H
#define SETTINGS_H

#include "minesweeper.h"


int set_cols(struct _win_st*, int);
int set_rows(struct _win_st*, int);
int set_nmines(struct _win_st*, int);
void init_colors();

#endif