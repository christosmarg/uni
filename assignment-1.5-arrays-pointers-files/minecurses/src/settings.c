#include "settings.h"

int set_cols(void)
{
    int cols;
    do
    {
        mvprintw(YMAX-4, 1, "Columns (Min = 5, Max = %d): ", (XMAX-2)/3-2);
		refresh();
        scanw("%d", &cols);
		refresh();
    } while (cols < 5 || cols > (XMAX-2)/3-2);
    return cols;    
}

int set_rows(void)
{
    int rows;
    do
    {
        mvprintw(YMAX-3, 1, "Rows (Min = 5, Max = %d): ", YMAX-4);
		refresh();
        scanw("%d", &rows);
		refresh();
    } while (rows < 5 || rows > YMAX-4); 
    return rows;
}

int set_nmines(int dimensions)
{
    int nmines;
    do
    {
        mvprintw(YMAX-2, 1, "Mines (Max = %d): ", dimensions-15);
        refresh();
        scanw("%d", &nmines);
        refresh();
    } while (nmines < 1 || nmines > dimensions-15);
    return nmines;
}
