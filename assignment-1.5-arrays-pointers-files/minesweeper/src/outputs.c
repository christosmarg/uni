#include "outputs.h"

void print_board(WINDOW *gameWin, char **board, int COLS, int ROWS)
{    
    int i, j, x, y = 1;

    print_grid(gameWin, ROWS, COLS);

    for (i = 0; i < ROWS; i++)
    {
        x = 2; 
        for (j = 0; j < COLS; j++)
        {
            wattron(gameWin, A_BOLD);
            mvwaddch(gameWin, y, x, board[i][j]);
            x += 3;
        }
        y++;
    }

    wrefresh(gameWin);
    wattron(gameWin, A_BOLD);
}


void print_grid(WINDOW *gameWin, int ROWS, int COLS)
{
    int i, j;

    for (i = 1; i <= ROWS; i++)
    {
        wmove(gameWin, i, 1);
        for (j = 0; j < COLS; j++)
            wprintw(gameWin, "[ ]");
    }

    wrefresh(gameWin);
}


void filewrite(char **mineboard, int COLS, int ROWS, int hitRow, int hitCol, const char *status)
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
            ? fprintf(mnsOut, "Mine hit at position (%d, %d)\n\n", hitRow+1, hitCol+1)
            : fprintf(mnsOut, "Last mine defused at position (%d, %d)\n\n", hitRow+1, hitCol+1);
        fprintf(mnsOut, "Board overview\n\n");

        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
                fprintf(mnsOut, "%c ", mineboard[i][j]);
            fprintf(mnsOut, "\n");
        }           

        mvprintw(1, 1, "Session written to file %s", CLEAR);
        refresh();
        getchar();
    }

    fclose(mnsOut);
}


void game_won(WINDOW *gameWin, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    wrefresh(gameWin);
    wattron(stdscr, A_BOLD);
    mvwprintw(stdscr, yMiddle-2, xMiddle-11, "You defused all the mines!");
    mvwprintw(stdscr, yMiddle-1, xMiddle-3, "You won :)");
    mvwprintw(stdscr, yMiddle, xMiddle-11, "Press any key to continue");
    refresh();
    wattroff(stdscr, A_BOLD);
}


void game_over(WINDOW *gameWin, char **mineboard, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    wrefresh(gameWin);
    wattron(stdscr, A_BOLD);
    mvwprintw(stdscr, yMiddle-2, xMiddle-22, "You hit a mine! (or tried defused the wrong cell)");
    mvwprintw(stdscr, yMiddle-1, xMiddle-4, "Game over :(");
    mvwprintw(stdscr, yMiddle, xMiddle-11, "Press any key to continue");
    refresh();
    wattroff(stdscr, A_BOLD);
}