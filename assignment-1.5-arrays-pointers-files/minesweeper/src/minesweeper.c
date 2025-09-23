#if defined linux || defined __unix__
#include <ncurses.h>
#elif defined _WIN32 || defined _WIN64
#include <pdcurses.h>
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "minesweeper.h"


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

    int WIDTH = set_width(menuWin, xMax);
    int HEIGHT = set_height(menuWin, yMax);
    int MINES = set_minesnum(menuWin, WIDTH * HEIGHT);

    game_win(WIDTH, HEIGHT, MINES);
    getchar();
}


int set_width(WINDOW *menuWin, int xMax)
{
    int WIDTH;

    do
    {
        mvwprintw(menuWin, 1, 1, "Width: ");
        wrefresh(menuWin);
        scanw("%d", &WIDTH);
        mvwprintw(menuWin, 1, strlen("Width: ") + 1, "%d", WIDTH);
        wrefresh(menuWin);
    } while (WIDTH < 5 || WIDTH > 114 /*WIDTH > xMax*/);

    return WIDTH;    
}


int set_height(WINDOW *menuWin, int yMax)
{
    int HEIGHT;

    do
    {
        mvwprintw(menuWin, 2, 1, "Height: ");
        wrefresh(menuWin);
        scanw("%d", &HEIGHT);
        mvwprintw(menuWin, 2, strlen("Height: ") + 1, "%d", HEIGHT);
        wrefresh(menuWin);
    } while (HEIGHT < 5 || HEIGHT > 41 /*HEIGHT > yMax*/);
    
    return HEIGHT;
}


int set_minesnum(WINDOW *menuWin, int DIMENSIONS)
{
    int MINES;

    do
    {
        mvwprintw(menuWin, 3, 1, "Mines: ");
        wrefresh(menuWin);
        scanw("%d", &MINES);
        mvwprintw(menuWin, 3, strlen("Mines: ") + 1, "%d", MINES);
        wrefresh(menuWin);
    } while (MINES < 1 || MINES > DIMENSIONS);
    
    return MINES;
}


void game_win(int WIDTH, int HEIGHT, int MINES)
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW *gameWin = newwin(43, xMax-10, (yMax/2) - 25, 5);
    box(gameWin, 0, 0);
    refresh();
    wrefresh(gameWin);
    keypad(gameWin, true);

    init_dispboard(gameWin, WIDTH, HEIGHT);
    init_mineboard(gameWin, WIDTH, HEIGHT, MINES);
}


void init_dispboard(WINDOW *gameWin, int WIDTH, int HEIGHT)
{
    int i;
    char **dispboard = (char **)malloc(WIDTH * sizeof(char *));
    for (i = 0; i < WIDTH; i++)
        *(dispboard + i) = (char *)malloc(HEIGHT);

    fill_dispboard(dispboard, WIDTH, HEIGHT);
    print(gameWin, dispboard, WIDTH, HEIGHT);
    getchar();
    
    free(dispboard);
}

void fill_dispboard(char **dispboard, int WIDTH, int HEIGHT)
{
    int i, j;

    for (i = 0; i < WIDTH; i++)
        for (j = 0; j < HEIGHT; j++)
            *(*(dispboard + i) + j) = '#';
}


void init_mineboard(WINDOW *gameWin, int WIDTH, int HEIGHT, int MINES)
{
    int i;
    char **mineboard = (char **)malloc(WIDTH * sizeof(char *));
    for (i = 0; i < WIDTH; i++)
        *(mineboard + i) = (char *)malloc(HEIGHT);

    fill_spaces(mineboard, WIDTH, HEIGHT, MINES);
    place_mines(mineboard, WIDTH, HEIGHT, MINES);
    adj_mines(mineboard, WIDTH, HEIGHT);

    print(gameWin, mineboard, WIDTH, HEIGHT);
    
    free(mineboard);
}


void place_mines(char **mineboard, int WIDTH, int HEIGHT, int MINES)
{
    int i, wRand, hRand;

    srand(time(NULL));

    for (i = 0; i < MINES; i++)
    {
        wRand = rand() % WIDTH;
        hRand = rand() % HEIGHT;
        *(*(mineboard + wRand) + hRand) = '*';
    }
}

    /* 
    Cell-->Current Cell (row, col) 
    N -->  North        (row-1, col) 
    S -->  South        (row+1, col) 
    E -->  East         (row, col+1) 
    W -->  West            (row, col-1) 
    N.E--> North-East   (row-1, col+1) 
    N.W--> North-West   (row-1, col-1) 
    S.E--> South-East   (row+1, col+1) 
    S.W--> South-West   (row+1, col-1) 
    */

    /*
    [x-1, y-1][x, y-1][x+1, y-1]
    [x-1, y  ][x, y  ][x+1, y  ]
    [x-1, y+1][x, y+1][x+1, y+1]
    */

void adj_mines(char **mineboard, int WIDTH, int HEIGHT)
{
    int row, col, numAdj = 0;

    for (row = 1; row <= WIDTH; row++)
    {
        for (col = 1; col <= HEIGHT; col++)
        {
            if (*(*(mineboard + (row - 1)) + col) != '*')
                numAdj++;
        }
    }

}


void fill_spaces(char **mineboard, int WIDTH, int HEIGHT, int MINES)
{
    int i, j;

    for (i = 0; i < WIDTH; i++)
    {
        for (j = 0; j < HEIGHT; j++)
        {
            if ((*(*mineboard + i) + j) != '*')
                *(*(mineboard + i) + j) = '-';
        }
    }
}


void print(WINDOW *gameWin, char **mineboard, int WIDTH, int HEIGHT)
{    
    int i, j;

    for (i = 0; i < WIDTH; i++)
    {
        for (j = 0; j < HEIGHT; j++)
        {
            mvwaddch(gameWin, j + 1, i + 1, *(*(mineboard + i) + j));
            wrefresh(gameWin);        
        }
    }
}