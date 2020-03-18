#include "navigation.h"

void navigate(WINDOW *gameWin, char **mineboard, char *move, int *mboardXLoc, int *mboardYLoc)
{
    int yMax, xMax;
    static int yLoc = 1, xLoc = 2;
    getmaxyx(gameWin, yMax, xMax);

    update_curs(gameWin, yLoc, xLoc);
    *mboardXLoc = (xLoc-2)/3;
    *mboardYLoc = yLoc-1;
    mvprintw(1, 1, "Current position: (%d, %d) ", *mboardXLoc, *mboardYLoc);
    refresh();
    getmv(gameWin, move, &yLoc, &xLoc, yMax, xMax);
}

void getmv(WINDOW *gameWin, char *move, int *yLoc, int *xLoc, int yMax, int xMax)
{
    *move = wgetch(gameWin);
    switch (*move) // vim keys support!!
    {
        case 'k': case 'K':
        case 'w': case 'W':
            mvup(yLoc);
            break;
        case 'j': case 'J':
        case 's': case 'S':
            mvdown(yLoc, yMax);
            break;
        case 'h': case 'H':
        case 'a': case 'A':
            mvleft(xLoc);
            break;
        case 'l': case 'L':
        case 'd': case 'D':
            mvright(xLoc, xMax);
            break;
    }
}

void mvup(int *yLoc)
{
    (*yLoc)--;
    if (*yLoc < 1) *yLoc = 1;
}

void mvdown(int *yLoc, int yMax)
{
    (*yLoc)++;
    if (*yLoc > yMax-2) *yLoc = yMax-2;
}

void mvleft(int *xLoc)
{
    *xLoc -= 3;
    if (*xLoc < 2) *xLoc = 2;
}

void mvright(int *xLoc, int xMax)
{
    *xLoc += 3;
    if (*xLoc > xMax-3) *xLoc = xMax-3;
}

void update_curs(WINDOW *gameWin, int yLoc, int xLoc)
{
    wmove(gameWin, yLoc, xLoc);
}
