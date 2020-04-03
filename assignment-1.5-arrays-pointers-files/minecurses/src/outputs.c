#include "outputs.h"

void print_board(WINDOW *gamew, char **board, int COLS, int ROWS)
{    
    int i, j, x, y = 1;

    print_grid(gamew, ROWS, COLS);

    for (i = 0; i < ROWS; i++)
    {
        x = 2; 
        for (j = 0; j < COLS; j++)
        {
            wattron(gamew, A_BOLD);
            mvwaddch(gamew, y, x, board[i][j]);
            x += 3;
        }
        y++;
    }

    wrefresh(gamew);
    wattron(gamew, A_BOLD);
}

void print_grid(WINDOW *gamew, int ROWS, int COLS)
{
    int i, j;

    for (i = 1; i <= ROWS; i++)
    {
        wmove(gamew, i, 1);
        for (j = 0; j < COLS; j++)
            wprintw(gamew, "[ ]");
    }

    wrefresh(gamew);
}

void session_write(char **mineboard, int COLS, int ROWS, int hitRow, int hitCol, const char *status)
{
    int i, j;
    FILE *mnsOut = fopen(SESSION_PATH, "w");

    if (mnsOut == NULL)
    {
        mvprintw(1, 1, "Error opening file, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else
    {
        strcmp(status, "won")
            ? fprintf(mnsOut, "Mine hit at position (%d, %d)\n\n", hitRow+1, hitCol+1)
            : fprintf(mnsOut, "Last mine defused at position (%d, %d)\n\n", hitRow+1, hitCol+1);
        fprintf(mnsOut, "Board overview\n\n");

        for (i = 0; i < ROWS; i++)
        {
            for (j = 0; j < COLS; j++)
                fprintf(mnsOut, "%c ", mineboard[i][j]);
            fprintf(mnsOut, "\n");
        }           

        mvprintw(1, 1, "Session written to file       ");
        refresh();
        getchar();
    }

    fclose(mnsOut);
}

void score_write(int numDefused, int COLS, int ROWS)
{
    FILE *scoreLog = fopen(SCORE_LOG_PATH, "a");
    char *playerName = get_pname();

    // add titles etc

    if (scoreLog == NULL)
    {
        mvprintw(1, 1, "Error opening file, exiting...");
        refresh();
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(scoreLog, "\n%s\t\t\t\t%d\t\t\t\t\t%dx%d", playerName, numDefused, COLS, ROWS);
        sort_scorelog(scoreLog); // pending
        mvprintw(1, 1, "New score written to score log");
        refresh();
        getchar();
    }
    
    fclose(scoreLog);
    free(playerName);
}

char *get_pname()
{   
    char buffer[20];
    char *playerName;

    move(1, 1);
    echo();
    clrtoeol();
    printw("Your name: ");
    refresh();
    scanw("%s", buffer);
    noecho();
    refresh();

    playerName = (char *)malloc(strlen(buffer) + 1);
    return (strcpy(playerName, buffer));
}

void sort_scorelog(FILE *scoreLog)
{

}

void game_won(WINDOW *gamew, int ymid, int xmid)
{
    wclear(gamew);
    wrefresh(gamew);
    wattron(stdscr, A_BOLD);
    mvwprintw(stdscr, ymid-2, xmid-11, "You defused all the mines!");
    mvwprintw(stdscr, ymid-1, xmid-3, "You won :)");
    mvwprintw(stdscr, ymid, xmid-11, "Press any key to continue");
    refresh();
    wattroff(stdscr, A_BOLD);
}

void game_over(WINDOW *gamew, char **mineboard, int ymid, int xmid)
{
    wclear(gamew);
    wrefresh(gamew);
    wattron(stdscr, A_BOLD);
    mvwprintw(stdscr, ymid-2, xmid-24, "You hit a mine! (or tried to defuse the wrong cell)");
    mvwprintw(stdscr, ymid-1, xmid-4, "Game over :(");
    mvwprintw(stdscr, ymid, xmid-11, "Press any key to continue");
    refresh();
    wattroff(stdscr, A_BOLD);
}
