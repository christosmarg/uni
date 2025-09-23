#include "outputs.h"

void print_grid(WINDOW *gameWin, int ROWS, int COLS)
{
    int i, j;
    for (j = 1; j <= ROWS; j++)
    {
        wmove(gameWin, j, 1);
        for (i = 0; i < COLS; i++)
            wprintw(gameWin, "[ ]");
    }
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


void print_board(WINDOW *gameWin, char **board, int COLS, int ROWS)
{    
    int i, j, x, y;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            mvwaddch(gameWin, j+1, i+1, board[i][j]);
            wrefresh(gameWin);
        }
    }
}


void filewrite(char **mineboard, int COLS, int ROWS, int hitCol, int hitRow, const char *status)
{
    int i, j;
    FILE *mnsOut = fopen("mnsout.txt", "w");

    if (mnsOut == NULL)
    {
        mvprintw(1, 1, "Error opening file, exiting...");
        exit(EXIT_FAILURE);
    }
    else
    {
        strcmp(status, "won")
            ? fprintf(mnsOut, "Mine hit at position (%d, %d)\n\n", hitCol, hitRow)
            : fprintf(mnsOut, "Last mine defused at position (%d, %d)\n\n", hitCol, hitRow);
        fprintf(mnsOut, "Board overview\n\n");

        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
                fprintf(mnsOut, "%c ", mineboard[j][i]);
            fprintf(mnsOut, "\n");
        }           

        mvprintw(1, 1, "Session written to file");
        refresh();
    }

    fclose(mnsOut);
}