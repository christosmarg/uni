#include <string.h>
#include "minesweeper.h"
#include "gameplay.h"

void selection(WINDOW *gameWin, char **dispboard, char **mineboard, int WIDTH, int HEIGHT)
{
    int chRow, chCol;
    bool gameOver;
    int yMax, xMax, yMiddle, xMiddle;
    getmaxyx(stdscr, yMax, xMax);
    yMiddle = yMax / 2;
    xMiddle = xMax / 2;

    do
    {
        mvprintw(1, 1, "Choice (row, col): ");
        scanw("%d %d", &chRow, &chCol);
        chRow++;
        chCol++;
        mvprintw(1, strlen("Choice (row, col): ") + 1, "(%d,%d)", chRow-1, chCol-1);
        refresh();
        mvprintw(1, 1, CLEAR);
        gameOver = transfer(dispboard, mineboard, chRow, chCol);
        reveal(gameWin, dispboard, chRow, chCol);
        getchar();
    } while (chRow < 0 || chRow > WIDTH-1 || chCol < 0 || chCol > HEIGHT-1 || !gameOver);
    
    if (gameOver == true)
    {
        game_over(gameWin, mineboard, yMiddle, xMiddle);
        getchar();
        print_board(gameWin, mineboard, WIDTH, HEIGHT);
        filewrite(mineboard, WIDTH, HEIGHT, chRow, chCol);
    }
}


bool transfer(char **dispboard, char **mineboard, int chRow, int chCol)
{
    dispboard[chRow][chCol] = mineboard[chRow][chCol];
    return (dispboard[chRow][chCol] == MINE) ? true : false;
}


void reveal(WINDOW *gameWin, char **dispboard, int chRow, int chCol)
{
    mvwaddch(gameWin, chRow, chCol, dispboard[chRow][chCol]);
    wrefresh(gameWin);
}

void game_over(WINDOW *gameWin, char **mineboard, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    mvwprintw(gameWin, yMiddle-11, xMiddle-11, "You hit a mine!");
    mvwprintw(gameWin, yMiddle-10, xMiddle-10, "Game over :(");
    wrefresh(gameWin);
    wclear(gameWin);
}