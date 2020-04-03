#include "settings.h"

int set_cols(WINDOW *menuw, int xmax)
{
    int COLS;

    do
    {
        mvwprintw(menuw, 1, 1, "Columns (Min = 5, Max = %d): ", (xmax-2)/3-2);
        wrefresh(menuw);
        scanw("%d", &COLS);
        mvwprintw(menuw, 1, COLS_CHAR_LENGTH, "%d", COLS);
        wrefresh(menuw);
    } while (COLS < 5 || COLS > (xmax-2)/3-2);

    return COLS;    
}

int set_rows(WINDOW *menuw, int ymax)
{
    int ROWS;

    do
    {
        mvwprintw(menuw, 2, 1, "Rows (Min = 5, Max = %d): ", ymax-14);
        wrefresh(menuw);
        scanw("%d", &ROWS);
        mvwprintw(menuw, 2, ROWS_CHAR_LENGTH, "%d", ROWS);
        wrefresh(menuw);
    } while (ROWS < 5 || ROWS > ymax - 14); 
    
    return ROWS;
}

int set_nmines(WINDOW *menuw, int DIMENSIONS)
{
    int NMINES;

    do
    {
        mvwprintw(menuw, 3, 1, "Mines (Max = %d): ", DIMENSIONS-15); // -10 so the player has a chance to win
        wrefresh(menuw);
        scanw("%d", &NMINES);
        mvwprintw(menuw, 3, NMINES_CHAR_LENGTH, "%d", NMINES);
        wrefresh(menuw);
    } while (NMINES < 1 || NMINES > DIMENSIONS-15);
    
    return NMINES;
}
