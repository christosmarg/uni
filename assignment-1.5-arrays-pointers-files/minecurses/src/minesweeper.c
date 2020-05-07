#include "minesweeper.h"

char **init_db(WINDOW *gamew, int cols, int rows)
{
    int i;
    char **db = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < rows; i++)
        db[i] = (char *)malloc(cols);

    if (db == NULL)
    {
        mvprintw(0, 0, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
	else fill_db(db, cols, rows);
    
    return db;
}

void fill_db(char **db, int cols, int rows)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			db[i][j] = BLANK;
}

char **init_mb(WINDOW *gamew, int cols, int rows, int nmines)
{
    int i;
    char **mb = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < rows; i++)
        mb[i] = (char *)malloc(cols);

    if (mb == NULL)
    {
        mvprintw(0, 0, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
	else
	{
		place_mines(mb, cols, rows, nmines);
		add_adj(mb, cols, rows);
		fill_spaces(mb, cols, rows, nmines);
	}
    
    return mb;
}

void place_mines(char **mb, int cols, int rows, int nmines)
{
	int i, wrand, hrand;
	srand(time(NULL));
	for (i = 0; i < nmines; i++)
	{
		wrand = rand() % rows;
		hrand = rand() % cols;
		mb[wrand][hrand] = MINE;
	}
}

void add_adj(char **mb, int cols, int rows)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			if (!is_mine(mb, i, j))
				mb[i][j] = adj_mines(mb, i, j, cols, rows) + '0';                
}

int is_mine(char **mb, int row, int col)
{
	return (mb[row][col] == MINE) ? TRUE : FALSE;
}

int outof_bounds(int row, int col, int cols, int rows)
{
	return (row < 0 || row > rows-1 || col < 0 || col > cols-1) ? TRUE : FALSE;
}

uint8_t adj_mines(char **mb, int row, int col, int cols, int rows)
{
	uint8_t nadj = 0;

	if (!outof_bounds(row, col-1, cols, rows)    && mb[row][col-1]    == MINE) nadj++; // north
	if (!outof_bounds(row, col+1, cols, rows)    && mb[row][col+1]    == MINE) nadj++; // south
	if (!outof_bounds(row+1, col, cols, rows)    && mb[row+1][col]    == MINE) nadj++; // east
	if (!outof_bounds(row-1, col, cols, rows)    && mb[row-1][col]    == MINE) nadj++; // west
	if (!outof_bounds(row+1, col-1, cols, rows)  && mb[row+1][col-1]  == MINE) nadj++; // north-east
	if (!outof_bounds(row-1, col-1, cols, rows)  && mb[row-1][col-1]  == MINE) nadj++; // north-west
	if (!outof_bounds(row+1, col+1, cols, rows)  && mb[row+1][col+1]  == MINE) nadj++; // south-east
	if (!outof_bounds(row-1, col+1, cols, rows)  && mb[row-1][col+1]  == MINE) nadj++; // south-west

	return nadj;
}

void fill_spaces(char **mb, int cols, int rows, int nmines)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			if (mb[i][j] != MINE && mb[i][j] == '0')
				mb[i][j] = '-';
}
