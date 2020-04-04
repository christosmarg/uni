#include "minesweeper.h"

char **init_dboard(WINDOW *gamew, int COLS, int ROWS)
{
    int i;
    char **dboard = (char **)malloc(ROWS * sizeof(char *));
    for (i = 0; i < ROWS; i++)
        dboard[i] = (char *)malloc(COLS);

    if (dboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else fill_dboard(dboard, COLS, ROWS);
    
    return dboard;
}

void fill_dboard(char **dboard, int COLS, int ROWS)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            dboard[i][j] = BLANK;
}

char **init_mboard(WINDOW *gamew, int COLS, int ROWS, int NMINES)
{
    int i;
    char **mboard = (char **)malloc(ROWS * sizeof(char *));
    for (i = 0; i < ROWS; i++)
        mboard[i] = (char *)malloc(COLS);

    if (mboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else
    {
        place_mines(mboard, COLS, ROWS, NMINES);
        add_adj(mboard, COLS, ROWS);
        fill_spaces(mboard, COLS, ROWS, NMINES);
    }
    
    return mboard;
}

void place_mines(char **mboard, int COLS, int ROWS, int NMINES)
{
    int i, wrand, hrand;

    srand(time(NULL));

    for (i = 0; i < NMINES; i++)
    {
        wrand = rand() % ROWS;
        hrand = rand() % COLS;
        mboard[wrand][hrand] = MINE;
    }
}

void add_adj(char **mboard, int COLS, int ROWS)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            if (!is_mine(mboard, i, j))
                mboard[i][j] = adj_mines(mboard, i, j, COLS, ROWS) + '0';                
}

bool is_mine(char **mboard, int row, int col)
{
    return (mboard[row][col] == MINE) ? true : false;
}

bool outof_bounds(int row, int col, int COLS, int ROWS)
{
    return (row < 0 || row > ROWS-1 || col < 0 || col > COLS-1) ? true : false;
}

int8_t adj_mines(char **mboard, int row, int col, int COLS, int ROWS)
{
    int8_t nadj = 0;

    if (!outof_bounds(row, col-1, COLS, ROWS)    && mboard[row][col-1]    == MINE) nadj++; // North
    if (!outof_bounds(row, col+1, COLS, ROWS)    && mboard[row][col+1]    == MINE) nadj++; // South
    if (!outof_bounds(row+1, col, COLS, ROWS)    && mboard[row+1][col]    == MINE) nadj++; // East
    if (!outof_bounds(row-1, col, COLS, ROWS)    && mboard[row-1][col]    == MINE) nadj++; // West
    if (!outof_bounds(row+1, col-1, COLS, ROWS)  && mboard[row+1][col-1]  == MINE) nadj++; // North-East
    if (!outof_bounds(row-1, col-1, COLS, ROWS)  && mboard[row-1][col-1]  == MINE) nadj++; // North-West
    if (!outof_bounds(row+1, col+1, COLS, ROWS)  && mboard[row+1][col+1]  == MINE) nadj++; // South-East
    if (!outof_bounds(row-1, col+1, COLS, ROWS)  && mboard[row-1][col+1]  == MINE) nadj++; // South-West

    return nadj;
}

void fill_spaces(char **mboard, int COLS, int ROWS, int NMINES)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            if (mboard[i][j] != MINE && mboard[i][j] == '0')
                mboard[i][j] = '-';
}
