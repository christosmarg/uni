#include "outputs.h"

void print_board(WINDOW *gamew, char **dboard, int COLS, int ROWS)
{    
    int i, j, x, y = 1;
    print_grid(gamew, ROWS, COLS);
	wattron(gamew, A_BOLD);
    for (i = 0; i < ROWS; i++)
    {
        x = 2; 
        for (j = 0; j < COLS; j++)
        {
            mvwaddch(gamew, y, x, dboard[i][j]);
            x += 3;
        }
        y++;
    }
}

void print_grid(WINDOW *gamew, int ROWS, int COLS)
{
    int i, j;
    wattroff(gamew, A_BOLD);
    for (i = 1; i <= ROWS; i++)
    {
        wmove(gamew, i, 1);
        for (j = 0; j < COLS; j++)
            wprintw(gamew, "[ ]");
    }
    wrefresh(gamew);
}

void session_info(int mbx, int mby, int xmax, int xmid, int ndefused, int NMINES)
{
	mvprintw(0, 0, "Current position: (%d, %d) ", mbx, mby);
	mvprintw(0, xmid-strlen("Defused mines: x/x")/2, "Defused mines: %d/%d", ndefused, NMINES);
	mvprintw(0, xmax-strlen("m Controls"), "m Controls");
}

void session_write(char **mboard, int COLS, int ROWS, int hitrow, int hitcol, const char *status)
{
    int i, j;
    FILE *mnsout = fopen(SESSION_PATH, "w");

    if (mnsout == NULL)
    {
        mvprintw(0, 0, "Error opening file, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else
    {
        strcmp(status, "won")
            ? fprintf(mnsout, "Mine hit at position (%d, %d)\n\n", hitrow+1, hitcol+1)
            : fprintf(mnsout, "Last mine defused at position (%d, %d)\n\n", hitrow+1, hitcol+1);
        fprintf(mnsout, "Board overview\n\n");

        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
                fprintf(mnsout, "%c ", mboard[i][j]);
            fprintf(mnsout, "\n");
        }           

        mvprintw(0, 0, "Session written to file       ");
        refresh();
        getchar();
    }

    fclose(mnsout);
}

void score_write(int ndefused, int COLS, int ROWS)
{
    FILE *scorelog = fopen(SCORE_LOG_PATH, "a");
    char *playername = get_pname();

    // add titles etc

    if (scorelog == NULL)
    {
        mvprintw(0, 0, "Error opening file, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(scorelog, "\n%s\t\t\t\t%d\t\t\t\t\t%dx%d", playername, ndefused, COLS, ROWS);
        sort_scorelog(scorelog); // pending
        mvprintw(0, 0, "New score written to score log");
        refresh();
        getchar();
    }
    
    fclose(scorelog);
    free(playername);
}

char *get_pname(void)
{   
    char buffer[20];
    char *playername;

    move(0, 0);
    echo();
    clrtoeol();
    printw("Your name: ");
    refresh();
    scanw("%s", buffer);
    noecho();
    refresh();

    playername = (char *)malloc(strlen(buffer) + 1);
    return (strcpy(playername, buffer));
}

void sort_scorelog(FILE *scorelog)
{

}

void game_won(WINDOW *gamew, int ymid, int xmid)
{
    wclear(gamew);
    wrefresh(gamew);
    attron(A_BOLD);
    mvprintw(ymid-2, xmid-11, "You defused all the mines!");
    mvprintw(ymid-1, xmid-3, "You won :)");
    mvprintw(ymid, xmid-11, "Press any key to continue");
    refresh();
    attroff(A_BOLD);
}

void game_over(WINDOW *gamew, char **mboard, int ymid, int xmid)
{
    wclear(gamew);
    wrefresh(gamew);
    attron(A_BOLD);
    mvprintw(ymid-2, xmid-24, "You hit a mine! (or tried to defuse the wrong cell)");
    mvprintw(ymid-1, xmid-4, "Game over :(");
    mvprintw(ymid, xmid-11, "Press any key to continue");
    refresh();
    attroff(A_BOLD);
}
