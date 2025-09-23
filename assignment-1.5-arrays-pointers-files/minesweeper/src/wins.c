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
}


WINDOW *menu_win(int *yMax, int *xMax)
{
    int numSettings = 3;
	getmaxyx(stdscr, *yMax, *xMax);
    WINDOW *menuWin = newwin(numSettings+2, *xMax-8, *yMax-7, 4);
    box(menuWin, 0, 0);
    wrefresh(menuWin);
    return menuWin;
}


WINDOW *game_win(int COLS, int ROWS, int NMINES)
{
    int winRows = ROWS + 2;
    int winCols = COLS*3 + 2;
    WINDOW *gameWin = newwin(winRows, winCols, 2, 4);
    box(gameWin, 0, 0);
    wrefresh(gameWin);
    return gameWin;
}


void options_menu()
{
    int yMax = getmaxy(stdscr);
    mvprintw(yMax-2, 1, "q Quit     m Manual"); // bold letters
    refresh();
}