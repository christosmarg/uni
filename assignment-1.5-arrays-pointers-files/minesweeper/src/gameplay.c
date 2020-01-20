#include "gameplay.h"

void selection(WINDOW *gameWin, char **dispboard, char **mineboard, int COLS, int ROWS, int NMINES)
{
    int chRow, chCol;
    bool gameOver;
    int numDefused = 0;
    int yMax, xMax, yMiddle, xMiddle;
    getmaxyx(stdscr, yMax, xMax);
    yMiddle = yMax / 2;
    xMiddle = xMax / 2;

    do
    {
        mvprintw(1, 1, "Choice (col, row): ");
        scanw("%d %d", &chCol, &chRow);
        mvprintw(1, strlen("Choice (col, row): ") + 1, "(%d,%d)", chCol, chRow);
        refresh();
        mvprintw(1, 1, CLEAR);
        gameOver = transfer(dispboard, mineboard, chCol, chRow, NMINES, &numDefused);
        mvprintw(1, xMiddle-9, "Defused mines: %d/%d", numDefused, NMINES);
        reveal(gameWin, dispboard, chCol, chRow);
        getchar();
    } while (((chCol >= 0 && chCol < COLS) && (chRow >= 0 && chRow < ROWS)) && numDefused < NMINES && !gameOver);
    
    if (gameOver == true)
    {
        game_over(gameWin, mineboard, yMiddle, xMiddle);
        getchar();
        print_board(gameWin, mineboard, COLS, ROWS);
        filewrite(mineboard, COLS, ROWS, chCol, chRow, "lost");
    }

    if (numDefused == NMINES)
    {
        game_won(gameWin, mineboard, yMiddle, xMiddle);
        getchar();
        filewrite(mineboard, COLS, ROWS, chCol, chRow, "won");
    }
}


bool transfer(char **dispboard, char **mineboard, int chCol, int chRow, int NMINES, int *numDefused)
{
    dispboard[chCol][chRow] = mineboard[chCol][chRow];
    return (!defused(dispboard, mineboard, chCol, chRow, NMINES, numDefused)) ? true : false;
}

bool defused(char **dispboard, char **mineboard, int chCol, int chRow, int NMINES, int *numDefused)
{
    char c = getchar();

    if (dispboard[chCol][chRow] == MINE)
    {
        if (c == DEFUSEKEY)
        {
            dispboard[chCol][chRow] = mineboard[chCol][chRow] = 'D';
            (*numDefused)++;
            return true;
        }
        else return false;
    }
}


void reveal(WINDOW *gameWin, char **dispboard, int chCol, int chRow)
{
    mvwaddch(gameWin, chRow+1, chCol+1, dispboard[chCol][chRow]);
    wrefresh(gameWin);
}


void game_won(WINDOW *gameWin, char **mineboard, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    mvwprintw(gameWin, yMiddle-11, xMiddle-18, "You defused all the mines!");
    mvwprintw(gameWin, yMiddle-10, xMiddle-10, "You won :)");
    wrefresh(gameWin);
    wclear(gameWin);
}


void game_over(WINDOW *gameWin, char **mineboard, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    mvwprintw(gameWin, yMiddle-11, xMiddle-11, "You hit a mine!");
    mvwprintw(gameWin, yMiddle-10, xMiddle-10, "Game over :(");
    wrefresh(gameWin);
    wclear(gameWin);
}