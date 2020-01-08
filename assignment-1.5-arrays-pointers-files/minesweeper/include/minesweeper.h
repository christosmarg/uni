#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdbool.h>


extern bool gameOver;

int set_width();
int set_height();
int set_mine_number();
void init();
void draw_table();
void place_mines();
void input();
void logic();


#endif