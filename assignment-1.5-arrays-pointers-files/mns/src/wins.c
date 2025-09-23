#include "wins.h"

void main_win()
{
    initscr();
    noecho();
    cbreak();
    
    WINDOW *mainWin = newwin(0, 0, 0, 0);
    box(mainWin, 0, 0);
    refresh();
    wrefresh(mainWin);
    keypad(mainWin, true);
}


void start()
{
    int yMax, xMax;
    int numSettings = 3;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *menuWin = newwin(numSettings+2, xMax-10, yMax-7, 5);
    box(menuWin, 0, 0);
    refresh();
    wrefresh(menuWin);
    keypad(menuWin, true);

    int COLS = set_cols(menuWin, xMax);
    int ROWS = set_rows(menuWin, yMax);
    int NMINES = set_nmines(menuWin, COLS * ROWS);

    delwin(menuWin);
    game_win(COLS, ROWS, NMINES);
    getchar();
}


void game_win(int COLS, int ROWS, int NMINES)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    WINDOW *gameWin = newwin(COLS, ROWS, 2, 3);

    box(gameWin, 0, 0);
    //mvwin(gameWin, (yMax/2) - 12, xMax/2);
    wrefresh(gameWin);
    refresh();

    char **dispboard = init_dispboard(gameWin, COLS, ROWS);
    char **mineboard = init_mineboard(gameWin, COLS, ROWS, NMINES);
    print_grid(gameWin, ROWS, COLS);
	selection(gameWin, dispboard, mineboard, COLS, ROWS, NMINES);

    free(dispboard);
    free(mineboard);
}
