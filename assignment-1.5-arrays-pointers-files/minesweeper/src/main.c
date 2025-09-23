#if defined linux || defined __unix__
#include <ncurses.h>
#elif defined _WIN32 || defined _WIN64
#include <pdcurses.h>
#endif

#include "minesweeper.h"


int main(int argc, char **argv)
{
    main_win();
    start();
    endwin();

    return 0;
}