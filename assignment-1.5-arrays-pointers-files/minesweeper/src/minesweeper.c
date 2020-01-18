#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "minesweeper.h"
#include "gameplay.h"

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

    int WIDTH = set_width(menuWin, xMax);
    int HEIGHT = set_height(menuWin, yMax);
    int NMINES = set_nmines(menuWin, WIDTH * HEIGHT);

    game_win(WIDTH, HEIGHT, NMINES);
    getchar();
}


void set_mode(WINDOW *menuWin) // loop
{
    char mode;
    mvwprintw(menuWin, 1, 1, "Keyboard or text mode (k/t): ");
    wrefresh(menuWin);
    scanw("%c", &mode);
    mvwprintw(menuWin, 1, strlen("Keyboard or text mode (k/t): ") + 1, "%c", mode);
    wrefresh(menuWin);
    mvwprintw(menuWin, 1, 1, CLEAR); // thanks stefastra && spyrosROUM!!!! :-DDDD
    wrefresh(menuWin);

    switch (mode)
    {
        case 'k':
        case 'K':
            mvwprintw(menuWin, 2, 1, "Keyboard mode");
            wrefresh(menuWin);
            break;
        case 't':
        case 'T':
            mvwprintw(menuWin, 2, 1, "Text mode");
            wrefresh(menuWin);
            break;
        default:
            break;
    }
}


int set_width(WINDOW *menuWin, int xMax)
{
    int WIDTH;

    do
    {
        mvwprintw(menuWin, 1, 1, "Width (Max = %d): ", xMax-12);
        wrefresh(menuWin);
        scanw("%d", &WIDTH);
        mvwprintw(menuWin, 1, strlen("Width (Max = XXX): ") + 1, "%d", WIDTH);
        wrefresh(menuWin);
    } while (WIDTH < 5 || WIDTH > xMax - 12);

    return WIDTH;    
}


int set_height(WINDOW *menuWin, int yMax)
{
    int HEIGHT;

    do
    {
        mvwprintw(menuWin, 2, 1, "Height (Max = %d): ", yMax-12);
        wrefresh(menuWin);
        scanw("%d", &HEIGHT);
        mvwprintw(menuWin, 2, strlen("Height (Max = YYY): ") + 1, "%d", HEIGHT);
        wrefresh(menuWin);
    } while (HEIGHT < 5 || HEIGHT > yMax - 12);
    
    return HEIGHT;
}


int set_nmines(WINDOW *menuWin, int DIMENSIONS)
{
    int NMINES;

    do
    {
        mvwprintw(menuWin, 3, 1, "Mines (Max = %d): ", DIMENSIONS-10); // -10 so the player has a chance to win
        wrefresh(menuWin);
        scanw("%d", &NMINES);
        mvwprintw(menuWin, 3, strlen("Mines (Max = MMMM): ") + 1, "%d", NMINES);
        wrefresh(menuWin);
    } while (NMINES < 1 || NMINES > DIMENSIONS-10);
    
    return NMINES;
}


void game_win(int WIDTH, int HEIGHT, int NMINES)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *gameWin = newwin(43, xMax-10, (yMax/2) - 24, 5); // fix 43
    box(gameWin, 0, 0);
    refresh();
    wrefresh(gameWin);
    keypad(gameWin, true);

    char **dispboard = init_dispboard(gameWin, WIDTH, HEIGHT);
    char **mineboard = init_mineboard(gameWin, WIDTH, HEIGHT, NMINES);

    selection(gameWin, dispboard, mineboard, WIDTH, HEIGHT);

    free(dispboard);
    free(mineboard);
}


char **init_dispboard(WINDOW *gameWin, int WIDTH, int HEIGHT)
{
    int i;
    char **dispboard = (char **)malloc(WIDTH * sizeof(char *));
    for (i = 0; i < WIDTH; i++)
        dispboard[i] = (char *)malloc(HEIGHT);

    if (dispboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        exit(EXIT_FAILURE);
    }
    else
    {
        fill_dispboard(dispboard, WIDTH, HEIGHT);
        print_board(gameWin, dispboard, WIDTH, HEIGHT);
        getchar();
    }
    
    return dispboard;
}

void fill_dispboard(char **dispboard, int WIDTH, int HEIGHT)
{
    int i, j;

    for (i = 0; i < WIDTH; i++)
        for (j = 0; j < HEIGHT; j++)
            dispboard[i][j] = HIDDEN;
}


char **init_mineboard(WINDOW *gameWin, int WIDTH, int HEIGHT, int NMINES)
{
    int i;
    char **mineboard = (char **)malloc(WIDTH * sizeof(char *));
    for (i = 0; i < WIDTH; i++)
        mineboard[i] = (char *)malloc(HEIGHT);

    if (mineboard == NULL)
    {
        mvprintw(1, 1, "Error, not enough memory, exiting...");
        exit(EXIT_FAILURE);
    }
    else
    {
        place_mines(mineboard, WIDTH, HEIGHT, NMINES);
        add_adj(mineboard, WIDTH, HEIGHT);
        fill_spaces(mineboard, WIDTH, HEIGHT, NMINES);
    }
    
    return mineboard;
}


void place_mines(char **mineboard, int WIDTH, int HEIGHT, int NMINES)
{
    int i, wRand, hRand;

    srand(time(NULL));

    for (i = 0; i < NMINES; i++)
    {
        wRand = rand() % WIDTH;
        hRand = rand() % HEIGHT;
        mineboard[wRand][hRand] = MINE;
    }
}


void add_adj(char **mineboard, int WIDTH, int HEIGHT)
{
    int i, j;

    for (i = 0; i < WIDTH; i++)
        for (j = 0; j < HEIGHT; j++)
            if (!is_mine(mineboard, i, j))
                mineboard[i][j] = adj_mines(mineboard, i, j, WIDTH, HEIGHT) + '0';                
}


bool is_mine(char **mineboard, int row, int col)
{
    return (mineboard[row][col] == MINE) ? true : false;
}

bool outof_bounds(int row, int col, int WIDTH, int HEIGHT)
{
    return (row < 0 || row > WIDTH-1 || col < 0 || col > HEIGHT-1) ? true : false;
}



int8_t adj_mines(char **mineboard, int row, int col, int WIDTH, int HEIGHT)
{
    int8_t numAdj = 0;

    if (!outof_bounds(row, col - 1, WIDTH, HEIGHT)      && mineboard[row][col-1]    == MINE) numAdj++; // North
    if (!outof_bounds(row, col + 1, WIDTH, HEIGHT)      && mineboard[row][col+1]    == MINE) numAdj++; // South
    if (!outof_bounds(row + 1, col, WIDTH, HEIGHT)      && mineboard[row+1][col]    == MINE) numAdj++; // East
    if (!outof_bounds(row - 1, col, WIDTH, HEIGHT)      && mineboard[row-1][col]    == MINE) numAdj++; // West
    if (!outof_bounds(row + 1, col - 1, WIDTH, HEIGHT)  && mineboard[row+1][col-1]  == MINE) numAdj++; // North-East
    if (!outof_bounds(row - 1, col - 1, WIDTH, HEIGHT)  && mineboard[row-1][col-1]  == MINE) numAdj++; // North-West
    if (!outof_bounds(row + 1, col + 1, WIDTH, HEIGHT)  && mineboard[row+1][col+1]  == MINE) numAdj++; // South-East
    if (!outof_bounds(row - 1, col + 1, WIDTH, HEIGHT)  && mineboard[row-1][col+1]  == MINE) numAdj++; // South-West

    return numAdj;
}


void fill_spaces(char **mineboard, int WIDTH, int HEIGHT, int NMINES)
{
    int i, j;

    for (i = 0; i < WIDTH; i++)
        for (j = 0; j < HEIGHT; j++)
            if (mineboard[i][j] != MINE && mineboard[i][j] == '0')
                mineboard[i][j] = '-';
}


void print_board(WINDOW *gameWin, char **mineboard, int WIDTH, int HEIGHT)
{    
    int i, j;

    for (i = 0; i < WIDTH; i++)
    {
        for (j = 0; j < HEIGHT; j++)
        {
            mvwaddch(gameWin, j + 1, i + 1, mineboard[i][j]);
            wrefresh(gameWin);
        }
    }
}


void filewrite(char **mineboard, int WIDTH, int HEIGHT, int hitRow, int hitCol)
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
        fprintf(mnsOut, "Mine hit at position (%d, %d)\n\n", hitRow, hitCol);
        fprintf(mnsOut, "Board overview\n\n");

        for (i = 0; i < WIDTH; i++) // fix inversion
        {
            for (j = 0; j < HEIGHT; j++)
                fprintf(mnsOut, "%c ", mineboard[i][j]);
            fprintf(mnsOut, "\n");
        }           

        mvprintw(1, 1, "Session written to file");
        refresh();
    }

    fclose(mnsOut);
}