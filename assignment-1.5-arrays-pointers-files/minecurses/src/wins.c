#include "wins.h"

void main_win()
{
    initscr();
    noecho();
    cbreak();
    
    WINDOW *mainWin = newwin(0, 0, 0, 0);
    wattron(mainWin, A_BOLD);
    box(mainWin, 0, 0);
    refresh();
    wrefresh(mainWin);
    wattroff(mainWin, A_BOLD);
}

WINDOW *menu_win(int *yMax, int *xMax)
{
    int numSettings = 3;
	getmaxyx(stdscr, *yMax, *xMax);
    WINDOW *menuWin = newwin(numSettings+2, *xMax-8, *yMax-8, 4);
    wattron(menuWin, A_BOLD);
    box(menuWin, 0, 0);
    wrefresh(menuWin);
    wattroff(menuWin, A_BOLD);
    return menuWin;
}

WINDOW *game_win(int COLS, int ROWS, int NMINES)
{
    int winRows = ROWS+2;
    int winCols = COLS*3+2;
    WINDOW *gameWin = newwin(winRows, winCols, 2, 4);
    wattron(gameWin, A_BOLD);
    box(gameWin, 0, 0);
    wrefresh(gameWin);
    wattroff(gameWin, A_BOLD);
    return gameWin;
}

void options_menu()
{
    int yMax = getmaxy(stdscr);
    mvprintw(yMax-3, 5, "q Quit          w/k Move up     s/j Move down       a/h Move Left       d/l Move Right      [ENTER]/o Open cell");
    mvprintw(yMax-2, 5, "f Flag cell     g Defuse (if flagged only)          p Pause music       + Volume up         - Volume down");
    refresh();
}
