#include "navigation.h"

void navigate(WINDOW *gameWin, char **mineboard, char *move, int *mboardXLoc, int *mboardYLoc)
{
    int yMax, xMax;
    static int yLoc = 1, xLoc = 2;
    getmaxyx(gameWin, yMax, xMax);
    wmove(gameWin, yLoc-1, xLoc);

    update_curs(gameWin, yLoc, xLoc);
    *mboardYLoc = yLoc-1;
    *mboardXLoc = (xLoc-2)/3;
    mvprintw(1, 1, "Current position: (%d, %d) ", *mboardXLoc+1, *mboardYLoc+1);
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
            mvup(yLoc, xLoc);
            break;
        case 'j': case 'J':
        case 's': case 'S':
            mvdown(yLoc, xLoc, yMax, xMax);
            break;
        case 'h': case 'H':
        case 'a': case 'A':
            mvleft(yLoc, xLoc);
            break;
        case 'l': case 'L':
        case 'd': case 'D':
            mvright(yLoc, xLoc, yMax, xMax);
            break;
        case 'f': case 'F':
            break;
        case '\n': 
            break;
        default: break;
    }
}


void mvup(int *yLoc, int *xLoc)
{
    (*yLoc)--;
    if (*yLoc < 1) *yLoc = 1;
}


void mvdown(int *yLoc, int *xLoc, int yMax, int xMax)
{
    (*yLoc)++;
    if (*yLoc > yMax-2) *yLoc = yMax-2;
}


void mvleft(int *yLoc, int *xLoc)
{
    *xLoc -= 3;
    if (*xLoc < 2) *xLoc = 2;
}


void mvright(int *yLoc, int *xLoc, int yMax, int xMax)
{
    *xLoc += 3;
    if (*xLoc > xMax-3) *xLoc = xMax-3;
}


void update_curs(WINDOW *gameWin, int yLoc, int xLoc)
{
    wmove(gameWin, yLoc, xLoc);
}