#include "minesweeper.h"

char **init_dboard(WINDOW *gamew, int cols, int rows)
{
    int i;
    char **dboard = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < rows; i++)
        dboard[i] = (char *)malloc(cols);

    if (dboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
	else fill_dboard(dboard, cols, rows);
    
    return dboard;
}

void fill_dboard(char **dboard, int cols, int rows)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			dboard[i][j] = BLANK;
}

char **init_mboard(WINDOW *gamew, int cols, int rows, int nmines)
{
    int i;
    char **mboard = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < rows; i++)
        mboard[i] = (char *)malloc(cols);

    if (mboard == NULL)
    {
        mvprintw(0, 0, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
	else
	{
		place_mines(mboard, cols, rows, nmines);
		add_adj(mboard, cols, rows);
		fill_spaces(mboard, cols, rows, nmines);
	}
    
    return mboard;
}

void place_mines(char **mboard, int cols, int rows, int nmines)
{
	int i, wrand, hrand;
	srand(time(NULL));
	for (i = 0; i < nmines; i++)
	{
		wrand = rand() % rows;
		hrand = rand() % cols;
		mboard[wrand][hrand] = MINE;
	}
}

void add_adj(char **mboard, int cols, int rows)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			if (!is_mine(mboard, i, j))
				mboard[i][j] = adj_mines(mboard, i, j, cols, rows) + '0';                
}

int is_mine(char **mboard, int row, int col)
{
	return (mboard[row][col] == MINE) ? true : false;
}

int outof_bounds(int row, int col, int cols, int rows)
{
	return (row < 0 || row > rows-1 || col < 0 || col > cols-1) ? true : false;
}

uint8_t adj_mines(char **mboard, int row, int col, int cols, int rows)
{
	int8_t nadj = 0;

	if (!outof_bounds(row, col-1, cols, rows)    && mboard[row][col-1]    == MINE) nadj++; // north
	if (!outof_bounds(row, col+1, cols, rows)    && mboard[row][col+1]    == MINE) nadj++; // south
	if (!outof_bounds(row+1, col, cols, rows)    && mboard[row+1][col]    == MINE) nadj++; // east
	if (!outof_bounds(row-1, col, cols, rows)    && mboard[row-1][col]    == MINE) nadj++; // west
	if (!outof_bounds(row+1, col-1, cols, rows)  && mboard[row+1][col-1]  == MINE) nadj++; // north-east
	if (!outof_bounds(row-1, col-1, cols, rows)  && mboard[row-1][col-1]  == MINE) nadj++; // north-west
	if (!outof_bounds(row+1, col+1, cols, rows)  && mboard[row+1][col+1]  == MINE) nadj++; // south-east
	if (!outof_bounds(row-1, col+1, cols, rows)  && mboard[row-1][col+1]  == MINE) nadj++; // south-west

	return nadj;
}

void fill_spaces(char **mboard, int cols, int rows, int nmines)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			if (mboard[i][j] != MINE && mboard[i][j] == '0')
				mboard[i][j] = '-';
}
