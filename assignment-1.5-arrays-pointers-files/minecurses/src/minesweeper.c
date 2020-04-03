#include "minesweeper.h"

char **init_dispboard(WINDOW *gamew, int COLS, int ROWS)
{
    int i;
    char **dispboard = (char **)malloc(ROWS * sizeof(char *));
    for (i = 0; i < ROWS; i++)
        dispboard[i] = (char *)malloc(COLS);

    if (dispboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else fill_dispboard(dispboard, COLS, ROWS);
    
    return dispboard;
}

void fill_dispboard(char **dispboard, int COLS, int ROWS)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            dispboard[i][j] = BLANK;
}

char **init_mineboard(WINDOW *gamew, int COLS, int ROWS, int NMINES)
{
    int i;
    char **mineboard = (char **)malloc(ROWS * sizeof(char *));
    for (i = 0; i < ROWS; i++)
        mineboard[i] = (char *)malloc(COLS);

    if (mineboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else
    {
        place_mines(mineboard, COLS, ROWS, NMINES);
        add_adj(mineboard, COLS, ROWS);
        fill_spaces(mineboard, COLS, ROWS, NMINES);
    }
    
    return mineboard;
}

void place_mines(char **mineboard, int COLS, int ROWS, int NMINES)
{
    int i, wRand, hRand;

    srand(time(NULL));

    for (i = 0; i < NMINES; i++)
    {
        wRand = rand() % ROWS;
        hRand = rand() % COLS;
        mineboard[wRand][hRand] = MINE;
    }
}

void add_adj(char **mineboard, int COLS, int ROWS)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            if (!is_mine(mineboard, i, j))
                mineboard[i][j] = adj_mines(mineboard, i, j, COLS, ROWS) + '0';                
}

bool is_mine(char **mineboard, int row, int col)
{
    return (mineboard[row][col] == MINE) ? true : false;
}

bool outof_bounds(int row, int col, int COLS, int ROWS)
{
    return (row < 0 || row > ROWS-1 || col < 0 || col > COLS-1) ? true : false;
}

int8_t adj_mines(char **mineboard, int row, int col, int COLS, int ROWS)
{
    int8_t numAdj = 0;

    if (!outof_bounds(row, col-1, COLS, ROWS)    && mineboard[row][col-1]    == MINE) numAdj++; // North
    if (!outof_bounds(row, col+1, COLS, ROWS)    && mineboard[row][col+1]    == MINE) numAdj++; // South
    if (!outof_bounds(row+1, col, COLS, ROWS)    && mineboard[row+1][col]    == MINE) numAdj++; // East
    if (!outof_bounds(row-1, col, COLS, ROWS)    && mineboard[row-1][col]    == MINE) numAdj++; // West
    if (!outof_bounds(row+1, col-1, COLS, ROWS)  && mineboard[row+1][col-1]  == MINE) numAdj++; // North-East
    if (!outof_bounds(row-1, col-1, COLS, ROWS)  && mineboard[row-1][col-1]  == MINE) numAdj++; // North-West
    if (!outof_bounds(row+1, col+1, COLS, ROWS)  && mineboard[row+1][col+1]  == MINE) numAdj++; // South-East
    if (!outof_bounds(row-1, col+1, COLS, ROWS)  && mineboard[row-1][col+1]  == MINE) numAdj++; // South-West

    return numAdj;
}

void fill_spaces(char **mineboard, int COLS, int ROWS, int NMINES)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            if (mineboard[i][j] != MINE && mineboard[i][j] == '0')
                mineboard[i][j] = '-';
}
