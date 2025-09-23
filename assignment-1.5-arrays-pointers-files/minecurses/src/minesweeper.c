#include "minesweeper.h"

void
init_db(WINDOW *gw, Board *b)
{
    int i;
    b->db = (char **)malloc(b->rows * sizeof(char *));
    for (i = 0; i < b->rows; i++)
        b->db[i] = (char *)malloc(b->cols);

    if (b->db == NULL)
    {
        mvprintw(0, 0, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
	else fill_db(b);
}

void
fill_db(Board *b)
{
	int i, j;
	for (i = 0; i < b->rows; i++)
		for (j = 0; j < b->cols; j++)
			b->db[i][j] = BLANK;
}

void
init_mb(WINDOW *gw, Board *b)
{
    int i;
    b->mb = (char **)malloc(b->rows * sizeof(char *));
    for (i = 0; i < b->rows; i++)
        b->mb[i] = (char *)malloc(b->cols);

    if (b->mb == NULL)
    {
        mvprintw(0, 0, "Error, not enough memory, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
	else
	{
		place_mines(b);
		add_adj(b);
		fill_spaces(b);
	}
}

void
place_mines(Board *b)
{
	int i, r, c;
	srand(time(NULL));
	for (i = 0; i < b->nmines; i++)
	{
		r = rand() % b->rows;
		c = rand() % b->cols;
		b->mb[r][c] = MINE;
	}
}

void
add_adj(Board *b)
{
	int i, j;
	for (i = 0; i < b->rows; i++)
		for (j = 0; j < b->cols; j++)
			if (!is_mine(b, i, j))
				b->mb[i][j] = adj_mines(b, i, j) + '0';                
}

int
is_mine(Board *b, int row, int col)
{
	return (b->mb[row][col] == MINE) ? TRUE : FALSE;
}

int
outof_bounds(Board *b, int row, int col)
{
	return (row < 0 || row > b->rows-1 || col < 0 || col > b->cols-1) ? TRUE : FALSE;
}

uint8_t
adj_mines(Board *b, int row, int col)
{
	uint8_t nadj = 0;

	if (!outof_bounds(b, row, col-1)	&& b->mb[row][col-1]    == MINE) nadj++; // north
	if (!outof_bounds(b, row, col+1)	&& b->mb[row][col+1]    == MINE) nadj++; // south
	if (!outof_bounds(b, row+1, col)	&& b->mb[row+1][col]    == MINE) nadj++; // east
	if (!outof_bounds(b, row-1, col)	&& b->mb[row-1][col]    == MINE) nadj++; // west
	if (!outof_bounds(b, row+1, col-1)  && b->mb[row+1][col-1]  == MINE) nadj++; // north-east
	if (!outof_bounds(b, row-1, col-1)  && b->mb[row-1][col-1]  == MINE) nadj++; // north-west
	if (!outof_bounds(b, row+1, col+1)  && b->mb[row+1][col+1]  == MINE) nadj++; // south-east
	if (!outof_bounds(b, row-1, col+1)  && b->mb[row-1][col+1]  == MINE) nadj++; // south-west

	return nadj;
}

void
fill_spaces(Board *b)
{
	int i, j;
	for (i = 0; i < b->rows; i++)
		for (j = 0; j < b->cols; j++)
			if (b->mb[i][j] != MINE && b->mb[i][j] == '0')
				b->mb[i][j] = '-';
}
