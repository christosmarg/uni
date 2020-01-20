#ifndef SETTINGS_H
#define SETTINGS_H

#include "minesweeper.h"

void set_mode(struct _win_st*);
int set_cols(struct _win_st*, int);
int set_rows(struct _win_st*, int);
int set_nmines(struct _win_st*, int);

#endif