#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#if defined linux || defined __unix__
#include <ncurses.h>
#elif defined _WIN32 || defined _WIN64
#include <pdcurses.h>
#include <stdint.h>
#endif

#include <stdbool.h>

#define HIDDEN '#'
#define MINE '*'

void main_win();
void start();
void set_mode(struct _win_st*);

int set_width(struct _win_st*, int);
int set_height(struct _win_st*, int);
int set_nmines(struct _win_st*, int);

void game_win(int, int, int);
void init_dispboard(struct _win_st*, int, int);
void fill_dispboard(char **, int, int);
void init_mineboard(struct _win_st*, int, int, int);
void place_mines(char **, int, int, int);
void add_adj(char **, int, int);
bool is_mine(char **, int, int);
uint8_t adj_mines(char **, int, int); // uint8_t so it has the same range as char

void fill_spaces(char **, int, int, int);

void selection();
void transfer(char **, char **, int, int);
void reveal(struct _win_st*, char **, char **, int, int);
void game_over(struct _win_st*);

void print(struct _win_st*, char **, int, int);
void filewrite(char **, int, int);

#endif