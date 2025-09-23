#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#if defined linux || defined __unix__
#include <ncurses.h>
#elif defined _WIN32 || defined _WIN64
#include <pdcurses.h>
#endif

#include <stdbool.h>

void main_win();
void start();

int set_width(struct _win_st*, int);
int set_height(struct _win_st*, int);
int set_minesnum(struct _win_st*, int);

void game_win(int, int, int);
void init_dispboard(struct _win_st*, int, int);
void fill_dispboard(char **, int, int);

void init_mineboard(struct _win_st*, int, int, int);
void place_mines(char **, int, int, int);
void adj_mines(char **, int, int);

void fill_spaces(char **, int, int, int);

bool is_mine(char **, int, int);
void transfer(char **, char **, int, int);
void reveal(struct _win_st*, char **, int, int);
void game_over(struct _win_st*);

void print(struct _win_st*, char **, int, int);

#endif