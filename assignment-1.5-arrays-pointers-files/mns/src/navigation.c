#include "navigation.h"

void navigate(WINDOW *gameWin, int COLS, int ROWS)
{
    keypad(gameWin, true);
    int move, i, j;
    int highlight = 0;


    for (i = 0; i < ROWS*COLS; i++)
    {
        if (i == highlight)
            wattron(gameWin, A_REVERSE);
        wattroff(gameWin, A_REVERSE);
    }

    switch (move)
    {
        case 'k':
        case 'K':
        case KEY_UP:
            highlight--;
            if (highlight == -1) highlight = 0;
            break;
        case 'j':
        case 'J':
        case KEY_DOWN:
            highlight++;
            if (highlight == COLS) highlight = COLS-1;
            break;
        case 'h':
        case 'H':
        case KEY_LEFT:
            highlight--;
            if (highlight == -1) highlight = 0;
            break;
        case 'l':
        case 'L':
        case KEY_RIGHT:
            highlight++;
            if (highlight == ROWS) highlight = ROWS-1;
            break;
        
        //if (move == 10) reveal(gameWin, dispboard, chCol, chRow);
    }
}