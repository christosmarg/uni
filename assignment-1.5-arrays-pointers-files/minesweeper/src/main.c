#include <stdio.h>
#include <stdbool.h>
#include "minesweeper.h"


int main(int argc, char **argv)
{
    int WIDTH = set_width();
    int HEIGHT = set_height();
    int MINE_NUMBER = set_mine_number();
    bool gameOver;
    
    init();
    
    if (!gameOver)
    {
        draw_table();
        place_mines();
        input();
        logic();
    }
    

    return 0;
}