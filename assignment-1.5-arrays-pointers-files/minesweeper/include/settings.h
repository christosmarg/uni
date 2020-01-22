#ifndef SETTINGS_H
#define SETTINGS_H

#include "minesweeper.h"

#define COLS_CHAR_LENGTH strlen("Columns (Max = XXX): ") + 1
#define ROWS_CHAR_LENGTH strlen("Rows (Max = YYY): ") + 1
#define NMINES_CHAR_LENGTH strlen("Mines (Max = MMMM): ") + 1

int set_cols(struct _win_st*, int);
int set_rows(struct _win_st*, int);
int set_nmines(struct _win_st*, int);
void init_colors();

#endif