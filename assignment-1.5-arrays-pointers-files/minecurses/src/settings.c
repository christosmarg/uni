#include "settings.h"

int set_cols(int ymax, int xmax)
{
    int COLS;
    do
    {
        mvprintw(ymax-4, 1, "Columns (Min = 5, Max = %d): ", (xmax-2)/3-2);
		refresh();
        scanw("%d", &COLS);
		refresh();
    } while (COLS < 5 || COLS > (xmax-2)/3-2);
    return COLS;    
}

int set_rows(int ymax)
{
    int ROWS;
    do
    {
        mvprintw(ymax-3, 1, "Rows (Min = 5, Max = %d): ", ymax-4);
		refresh();
        scanw("%d", &ROWS);
		refresh();
    } while (ROWS < 5 || ROWS > ymax-4); 
    return ROWS;
}

int set_nmines(int ymax, int DIMENSIONS)
{
    int NMINES;
    do
    {
        mvprintw(ymax-2, 1, "Mines (Max = %d): ", DIMENSIONS-15); // -10 so the player has a chance to win
        refresh();
        scanw("%d", &NMINES);
        refresh();
    } while (NMINES < 1 || NMINES > DIMENSIONS-15);
    return NMINES;
}
