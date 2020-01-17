#include <string.h>
#include "minesweeper.h"
#include "gamelogic.h"

void selection(WINDOW *gameWin, char **dispboard, char **mineboard, int WIDTH, int HEIGHT)
{
    int chrow, chcol;
    bool gameOver = true;
    int yMax, xMax, yMiddle, xMiddle;
    getmaxyx(gameWin, yMax, xMax);
    yMiddle = yMax / 2;
    xMiddle = xMax / 2;

    do
    {
        mvprintw(1, 1, "Choice (row, col): ");
        scanw("%d %d", &chrow, &chcol);
        chrow++;
        chcol++;
        mvprintw(1, strlen("Choice (row, col): ") + 1, "(%d,%d)", chrow-1, chcol-1);
        refresh();
        mvprintw(1, 1, CLEAR);
        transfer(dispboard, mineboard, chrow, chcol);
        reveal(gameWin, dispboard, chrow, chcol);   
        getchar();
    } while ((chrow < 0 || chrow > WIDTH-1 || chcol < 0 || chcol > HEIGHT-1) && !gameOver);
    
    if (gameOver)
    {
        game_over(gameWin, mineboard, yMiddle, xMiddle);
        print(gameWin, mineboard, WIDTH, HEIGHT);
        filewrite(mineboard, WIDTH, HEIGHT);
    }
}


bool transfer(char **dispboard, char **mineboard, int chrow, int chcol)
{
    dispboard[chrow][chcol] = mineboard[chrow][chcol];
    return (dispboard[chrow][chcol] == MINE) ? true : false;
}


void reveal(WINDOW *gameWin, char **dispboard, int chrow, int chcol)
{
    mvwaddch(gameWin, chrow, chcol, dispboard[chrow][chcol]);
    wrefresh(gameWin);
}

void game_over(WINDOW *gameWin, char **mineboard, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    mvwprintw(gameWin, yMiddle, xMiddle, "Game over :(");
    wrefresh(gameWin);
}