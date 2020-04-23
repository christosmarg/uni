#include "settings.h"

int set_cols()
{
    int COLS;
    do
    {
        mvprintw(YMAX-4, 1, "Columns (Min = 5, Max = %d): ", (XMAX-2)/3-2);
		refresh();
        scanw("%d", &COLS);
		refresh();
    } while (COLS < 5 || COLS > (XMAX-2)/3-2);
    return COLS;    
}

int set_rows()
{
    int ROWS;
    do
    {
        mvprintw(YMAX-3, 1, "Rows (Min = 5, Max = %d): ", YMAX-4);
		refresh();
        scanw("%d", &ROWS);
		refresh();
    } while (ROWS < 5 || ROWS > YMAX-4); 
    return ROWS;
}

int set_nmines(int DIMENSIONS)
{
    int NMINES;
    do
    {
        mvprintw(YMAX-2, 1, "Mines (Max = %d): ", DIMENSIONS-15); // -10 so the player has a chance to win
        refresh();
        scanw("%d", &NMINES);
        refresh();
    } while (NMINES < 1 || NMINES > DIMENSIONS-15);
    return NMINES;
}
