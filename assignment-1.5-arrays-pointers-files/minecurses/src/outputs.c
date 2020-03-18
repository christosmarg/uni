#include "outputs.h"

void print_board(WINDOW *gameWin, char **board, int COLS, int ROWS)
{    
    int i, j, x, y = 1;

    print_grid(gameWin, ROWS, COLS);

    for (i = 0; i < ROWS; i++)
    {
        x = 2; 
        for (j = 0; j < COLS; j++)
        {
            wattron(gameWin, A_BOLD);
            mvwaddch(gameWin, y, x, board[i][j]);
            x += 3;
        }
        y++;
    }

    wrefresh(gameWin);
    wattron(gameWin, A_BOLD);
}

void print_grid(WINDOW *gameWin, int ROWS, int COLS)
{
    int i, j;

    for (i = 1; i <= ROWS; i++)
    {
        wmove(gameWin, i, 1);
        for (j = 0; j < COLS; j++)
            wprintw(gameWin, "[ ]");
    }

    wrefresh(gameWin);
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

void game_won(WINDOW *gameWin, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    wrefresh(gameWin);
    wattron(stdscr, A_BOLD);
    mvwprintw(stdscr, yMiddle-2, xMiddle-11, "You defused all the mines!");
    mvwprintw(stdscr, yMiddle-1, xMiddle-3, "You won :)");
    mvwprintw(stdscr, yMiddle, xMiddle-11, "Press any key to continue");
    refresh();
    wattroff(stdscr, A_BOLD);
}

void game_over(WINDOW *gameWin, char **mineboard, int yMiddle, int xMiddle)
{
    wclear(gameWin);
    wrefresh(gameWin);
    wattron(stdscr, A_BOLD);
    mvwprintw(stdscr, yMiddle-2, xMiddle-24, "You hit a mine! (or tried to defuse the wrong cell)");
    mvwprintw(stdscr, yMiddle-1, xMiddle-4, "Game over :(");
    mvwprintw(stdscr, yMiddle, xMiddle-11, "Press any key to continue");
    refresh();
    wattroff(stdscr, A_BOLD);
}
