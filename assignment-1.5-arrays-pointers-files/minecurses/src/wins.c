#include "wins.h"

void main_win(void)
{
    initscr();
    noecho();
    cbreak();
    
    WINDOW *mainw = newwin(0, 0, 0, 0);
    wattron(mainw, A_BOLD);
    box(mainw, 0, 0);
    refresh();
    wrefresh(mainw);
    wattroff(mainw, A_BOLD);
}

WINDOW *menu_win(int *ymax, int *xmax)
{
    int nsettings = 3;
	getmaxyx(stdscr, *ymax, *xmax);
    WINDOW *menuw = newwin(nsettings+2, *xmax-8, *ymax-8, 4);
    wattron(menuw, A_BOLD);
    box(menuw, 0, 0);
    wrefresh(menuw);
    wattroff(menuw, A_BOLD);
    return menuw;
}

WINDOW *game_win(int COLS, int ROWS, int NMINES)
{
    int wrows = ROWS+2;
    int wcols = COLS*3+2;
    WINDOW *gameWin = newwin(wrows, wcols, 2, 4);
    wattron(gameWin, A_BOLD);
    box(gameWin, 0, 0);
    wrefresh(gameWin);
    wattroff(gameWin, A_BOLD);
    return gameWin;
}

void options_menu(void)
{
    int ymax = getmaxy(stdscr);
    mvprintw(ymax-3, 5, "q Quit          w/k Move up     s/j Move down       a/h Move Left       d/l Move Right      [ENTER]/o Open cell");
    mvprintw(ymax-2, 5, "f Flag cell     g Defuse (if flagged only)          p Pause music       + Volume up         - Volume down");
    refresh();
}
