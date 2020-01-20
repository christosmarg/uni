#include "outputs.h"

void print_board(WINDOW *gameWin, char **mineboard, int COLS, int ROWS)
{    
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            mvwaddch(gameWin, j+1, i+1, mineboard[i][j]);
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