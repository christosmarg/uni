#include "minesweeper.h"

void main_win()
{
    initscr();
    noecho();
    cbreak();
    
    WINDOW *mainWin = newwin(0, 0, 0, 0);
    box(mainWin, 0, 0);
    refresh();
    wrefresh(mainWin);
    keypad(mainWin, true);
}


void start()
{
    int yMax, xMax;
    int numSettings = 3;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *menuWin = newwin(numSettings+2, xMax-10, yMax-7, 5);
    box(menuWin, 0, 0);
    refresh();
    wrefresh(menuWin);
    keypad(menuWin, true);

    set_mode(menuWin);

    int COLS = set_cols(menuWin, xMax);
    int ROWS = set_rows(menuWin, yMax);
    int NMINES = set_nmines(menuWin, COLS * ROWS);

    game_win(COLS, ROWS, NMINES);
    getchar();
}


void game_win(int COLS, int ROWS, int NMINES)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *gameWin = newwin(43, xMax-10, (yMax/2) - 24, 5); // fix 43
    box(gameWin, 0, 0);
    refresh();
    wrefresh(gameWin);
    keypad(gameWin, true);

    char **dispboard = init_dispboard(gameWin, COLS, ROWS);
    char **mineboard = init_mineboard(gameWin, COLS, ROWS, NMINES);

	selection(gameWin, dispboard, mineboard, COLS, ROWS, NMINES);

    free(dispboard);
    free(mineboard);
}


char **init_dispboard(WINDOW *gameWin, int COLS, int ROWS)
{
    int i;
    char **dispboard = (char **)malloc(COLS * sizeof(char *));
    for (i = 0; i < COLS; i++)
        dispboard[i] = (char *)malloc(ROWS);

    if (dispboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        exit(EXIT_FAILURE);
    }
    else
    {
        fill_dispboard(dispboard, COLS, ROWS);
        print_board(gameWin, dispboard, COLS, ROWS);
        getchar();
    }
    
    return dispboard;
}


void fill_dispboard(char **dispboard, int COLS, int ROWS)
{
    int i, j;

    for (i = 0; i < COLS; i++)
        for (j = 0; j < ROWS; j++)
            dispboard[i][j] = HIDDEN;
}


char **init_mineboard(WINDOW *gameWin, int COLS, int ROWS, int NMINES)
{
    int i;
    char **mineboard = (char **)malloc(COLS * sizeof(char *));
    for (i = 0; i < COLS; i++)
        mineboard[i] = (char *)malloc(ROWS);

    if (mineboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        exit(EXIT_FAILURE);
    }
    else
    {
        place_mines(mineboard, COLS, ROWS, NMINES);
        add_adj(mineboard, COLS, ROWS);
        fill_spaces(mineboard, COLS, ROWS, NMINES);

        // tests
        //print_board(gameWin, mineboard, COLS, ROWS);
        //filewrite(mineboard, COLS, ROWS, 1, 2);
    }
    
    return mineboard;
}


void place_mines(char **mineboard, int COLS, int ROWS, int NMINES)
{
    int i, wRand, hRand;

    srand(time(NULL));

    for (i = 0; i < NMINES; i++)
    {
        wRand = rand() % COLS;
        hRand = rand() % ROWS;
        mineboard[wRand][hRand] = MINE;
    }
}


void add_adj(char **mineboard, int COLS, int ROWS)
{
    int i, j;

    for (i = 0; i < COLS; i++)
        for (j = 0; j < ROWS; j++)
            if (!is_mine(mineboard, i, j))
                mineboard[i][j] = adj_mines(mineboard, i, j, COLS, ROWS) + '0';                
}


bool is_mine(char **mineboard, int row, int col)
{
    return (mineboard[row][col] == MINE) ? true : false;
}

bool outof_bounds(int row, int col, int COLS, int ROWS)
{
    return (row < 0 || row > COLS-1 || col < 0 || col > ROWS-1) ? true : false;
}



int8_t adj_mines(char **mineboard, int row, int col, int COLS, int ROWS)
{
    int8_t numAdj = 0;

    if (!outof_bounds(row, col - 1, COLS, ROWS)      && mineboard[row][col-1]    == MINE) numAdj++; // North
    if (!outof_bounds(row, col + 1, COLS, ROWS)      && mineboard[row][col+1]    == MINE) numAdj++; // South
    if (!outof_bounds(row + 1, col, COLS, ROWS)      && mineboard[row+1][col]    == MINE) numAdj++; // East
    if (!outof_bounds(row - 1, col, COLS, ROWS)      && mineboard[row-1][col]    == MINE) numAdj++; // West
    if (!outof_bounds(row + 1, col - 1, COLS, ROWS)  && mineboard[row+1][col-1]  == MINE) numAdj++; // North-East
    if (!outof_bounds(row - 1, col - 1, COLS, ROWS)  && mineboard[row-1][col-1]  == MINE) numAdj++; // North-West
    if (!outof_bounds(row + 1, col + 1, COLS, ROWS)  && mineboard[row+1][col+1]  == MINE) numAdj++; // South-East
    if (!outof_bounds(row - 1, col + 1, COLS, ROWS)  && mineboard[row-1][col+1]  == MINE) numAdj++; // South-West

    return numAdj;
}


void fill_spaces(char **mineboard, int COLS, int ROWS, int NMINES)
{
    int i, j;

    for (i = 0; i < COLS; i++)
        for (j = 0; j < ROWS; j++)
            if (mineboard[i][j] != MINE && mineboard[i][j] == '0')
                mineboard[i][j] = '-';
}