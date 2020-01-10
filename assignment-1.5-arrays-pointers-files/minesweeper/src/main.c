#if defined linux || defined __unix__
#include <ncurses.h>
#elif defined _WIN32 || defined _WIN64
#include <pdcurses.h>
#endif

#include <stdbool.h>
#include "minesweeper.h"


int main(int argc, char **argv)
{
    initscr();
    noecho();
    cbreak();
    
    WINDOW *mainWin = newwin(0, 0, 0, 0);
    box(mainWin, 0, 0);
    refresh();
    wrefresh(mainWin);
    keypad(mainWin, true);

    start();

    endwin();

    return 0;
}