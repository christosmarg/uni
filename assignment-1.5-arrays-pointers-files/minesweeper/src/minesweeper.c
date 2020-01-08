#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "minesweeper.h"
#include "ccolors.h"


int set_width()
{
    int WIDTH;

    do
    {
        printf("Width (between 10 and 100): ");
        scanf("%d", &WIDTH);
    } while (WIDTH < 10 || WIDTH > 100);
    

    return WIDTH;
}


int set_height()
{
    int HEIGHT;

    do
    {
        printf("Height (between 10 and 100): ");
        scanf("%d", &HEIGHT);
    } while (HEIGHT < 10 || HEIGHT > 100);
    

    return HEIGHT;
}


int set_mine_number()
{
    int MINE_NUMBER;

    do
    {
        printf("Number of mines (between 1 and 20): ");
        scanf("%d", &MINE_NUMBER);
    } while (MINE_NUMBER <= 0 || MINE_NUMBER > 20);
    

    return MINE_NUMBER;
}


void init(int WIDTH, int HEIGHT)
{   
    bool gameOver = false;

    int mineX = rand() % WIDTH;
    int mineY = rand() % HEIGHT;
}


void draw_table(int WIDTH, int HEIGHT)
{

}


void place_mines()
{

}


void input()
{

}


void logic()
{

}