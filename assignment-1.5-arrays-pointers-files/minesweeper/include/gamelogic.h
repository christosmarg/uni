#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#if defined linux || defined __unix__
#include <ncurses.h>
#elif defined _WIN32 || defined _WIN64
#include <pdcurses.h>
#include <stdint.h>
#endif

#include <stdbool.h>

// Game logic
void selection(struct _win_st*, char **, char **, int, int);
bool transfer(char **, char **, int, int);
void reveal(struct _win_st*, char **, int, int);
void game_over(struct _win_st*, char **, int, int);

#endif