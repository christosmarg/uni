#include "navigation.h"

void navigate(WINDOW *gamew, char **mboard, char *move, int *mbx, int *mby)
{
    int ymax, xmax;
    static int y = 1, x = 2;
    getmaxyx(gamew, ymax, xmax);
    update_curs(gamew, y, x);
    *mbx = (x-2)/3;
    *mby = y-1;
    refresh();
    getmv(gamew, move, &y, &x, ymax, xmax);
}

void getmv(WINDOW *gamew, char *move, int *y, int *x, int ymax, int xmax)
{
    *move = wgetch(gamew);
    switch (*move) // vim keys support!!
    {
        case 'k': case 'K':
        case 'w': case 'W':
            mvup(y);
            break;
        case 'j': case 'J':
        case 's': case 'S':
            mvdown(y, ymax);
            break;
        case 'h': case 'H':
        case 'a': case 'A':
            mvleft(x);
            break;
        case 'l': case 'L':
        case 'd': case 'D':
            mvright(x, xmax);
            break;
    }
}

void mvup(int *y)
{
    (*y)--;
    if (*y < 1) *y = 1;
}

void mvdown(int *y, int ymax)
{
    (*y)++;
    if (*y > ymax-2) *y = ymax-2;
}

void mvleft(int *x)
{
    *x -= 3;
    if (*x < 2) *x = 2;
}

void mvright(int *x, int xmax)
{
    *x += 3;
    if (*x > xmax-3) *x = xmax-3;
}

void update_curs(WINDOW *gamew, int y, int x)
{
    wmove(gamew, y, x);
}
