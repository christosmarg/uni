#include "settings.h"

int set_cols(WINDOW *menuWin, int xMax)
{
    int COLS;

    do
    {
        mvwprintw(menuWin, 1, 1, "Columns (Max = %d): ", (xMax-2)/3 - 2);
        wrefresh(menuWin);
        scanw("%d", &COLS);
        mvwprintw(menuWin, 1, strlen("Columns (Max = XXX): ") + 1, "%d", COLS);
        wrefresh(menuWin);
    } while (COLS < 5 || COLS > (xMax-2)/3 - 2);

    return COLS;    
}


int set_rows(WINDOW *menuWin, int yMax)
{
    int ROWS;

    do
    {
        mvwprintw(menuWin, 2, 1, "Rows (Max = %d): ", yMax-14);
        wrefresh(menuWin);
        scanw("%d", &ROWS);
        mvwprintw(menuWin, 2, strlen("Rows (Max = YYY): ") + 1, "%d", ROWS);
        wrefresh(menuWin);
    } while (ROWS < 5 || ROWS > yMax - 14);
    
    return ROWS;
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


void init_colors()
{

}