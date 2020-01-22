#include "gameplay.h"

void play_minesweeper(WINDOW *gameWin, char **dispboard, char **mineboard, int COLS, int ROWS, int NMINES)
{
    int mboardXLoc = 0, mboardYLoc = 0;
    bool gameOver = false, cantFlag = false;
    int numDefused = 0, numFlagged = 0;
    int yMax, xMax, yMiddle, xMiddle;
    char move;
    getmaxyx(stdscr, yMax, xMax);
    yMiddle = yMax / 2;
    xMiddle = xMax / 2;

    do
    {
        navigate(gameWin, dispboard, &move, &mboardXLoc, &mboardYLoc);
        
        if (move == '\n' || move == 'o' || move == 'O') // handle cell opening
        {
            transfer(dispboard, mineboard, mboardYLoc, mboardXLoc);
            reveal(gameWin, dispboard, mboardYLoc, mboardXLoc, mboardYLoc + 1, 3*mboardXLoc + 2);
            //cantFlag = true;
            if (dispboard[mboardYLoc][mboardXLoc] == MINE) gameOver = true;
        }
        else if (move == 'f' || move == 'F') // handle falgs
        {
            if (dispboard[mboardYLoc][mboardXLoc] == 'F') // undo flag
                dispboard[mboardYLoc][mboardXLoc] = ' ';
            else
                dispboard[mboardYLoc][mboardXLoc] = 'F';
                // handle already defused mine 
            reveal(gameWin, dispboard, mboardYLoc, mboardXLoc, mboardYLoc + 1, 3*mboardXLoc + 2);
        }
        else if (move == 'g' || move == 'G') // check for defuse
        {
            if (dispboard[mboardYLoc][mboardXLoc] == 'F' && mineboard[mboardYLoc][mboardXLoc] == MINE) // is_mine replace
            {
                numDefused++;
                refresh();
                dispboard[mboardYLoc][mboardXLoc] = mineboard[mboardYLoc][mboardXLoc] = 'D';
                reveal(gameWin, dispboard, mboardYLoc, mboardXLoc, mboardYLoc + 1, 3*mboardXLoc + 2);
            }
            // handle false defusal
            // handle already defused mine           
        }

        mvprintw(1, xMiddle-8, "Defused mines: %d/%d", numDefused, NMINES);
        
    } while (((mboardYLoc >= 0 && mboardYLoc < COLS) && (mboardXLoc >= 0 && mboardXLoc < ROWS)) &&
             numDefused < NMINES && !gameOver && move != 'q');
    
    if (gameOver == true)
    {
        game_over(gameWin, mineboard, yMiddle, xMiddle);
        getchar();
        print_board(gameWin, mineboard, COLS, ROWS);
        filewrite(mineboard, COLS, ROWS, mboardXLoc, mboardYLoc, "lost");
    }

    if (numDefused == NMINES)
    {
        game_won(gameWin, yMiddle, xMiddle);
        getchar();
        filewrite(mineboard, COLS, ROWS, mboardXLoc, mboardYLoc, "won");
    }
}


void transfer(char **dispboard, char **mineboard, int mboardYLoc, int mboardXLoc)
{
    dispboard[mboardYLoc][mboardXLoc] = mineboard[mboardYLoc][mboardXLoc];
}


void reveal(WINDOW *gameWin, char **dispboard, int mboardYLoc, int mboardXLoc, int yLoc, int xLoc)
{
    mvwaddch(gameWin, yLoc, xLoc, dispboard[mboardYLoc][mboardXLoc]);
    wrefresh(gameWin);
}


void flag_handler()
{

}


bool is_flagged()
{

}


bool is_defused(char **dispboard, char **mineboard, int mboardYLoc, int mboardXLoc)
{
    return ((dispboard[mboardYLoc][mboardXLoc] == 'D')) ? true : false;
}