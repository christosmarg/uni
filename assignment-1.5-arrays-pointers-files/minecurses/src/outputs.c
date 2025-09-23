#include "outputs.h"

void print_board(WINDOW *gamew, Board *brd)
{    
	int i, j, x, y = 1;
	print_grid(gamew, brd->rows, brd->cols);
	wattron(gamew, A_BOLD);
	for (i = 0; i < brd->rows; i++)
	{
		x = 2; 
		for (j = 0; j < brd->cols; j++)
		{
			mvwaddch(gamew, y, x, brd->db[i][j]);
			x += 3;
		}
		y++;
	}
}

void print_grid(WINDOW *gamew, int rows, int cols)
{
	int i, j;
	wattroff(gamew, A_BOLD);
	for (i = 1; i <= rows; i++)
	{
		wmove(gamew, i, 1);
		for (j = 0; j < cols; j++)
			wprintw(gamew, "[ ]");
	}
	wrefresh(gamew);
}

void session_info(int mbx, int mby, int xmid, int ndefused, int nmines)
{
	mvprintw(0, 0, "Current position: (%d, %d) ", mbx, mby);
	mvprintw(0, xmid-strlen("Defused mines: x/x")/2, "Defused mines: %d/%d", ndefused, nmines);
	mvprintw(0, XMAX-strlen("m Controls"), "m Controls");
}

void session_write(Board *brd, int hitrow, int hitcol, const char *status)
{
	int i, j;
	FILE *fsession = fopen(SESSION_PATH, "w");
	if (fsession == NULL)
	{
		mvprintw(0, 0, "Error opening file, exiting...");
		refresh();
		exit(EXIT_FAILURE);
	}
	else
	{
		strcmp(status, "won")
			? fprintf(fsession, "Mine hit at position (%d, %d)\n\n", hitrow+1, hitcol+1)
			: fprintf(fsession, "Last mine defused at position (%d, %d)\n\n", hitrow+1, hitcol+1);
		fprintf(fsession, "Board overview\n\n");
		for (i = 0; i < brd->rows; i++)
		{
			for (j = 0; j < brd->cols; j++)
				fprintf(fsession, "%c ", brd->mb[i][j]);
			fprintf(fsession, "\n");
		}           
	}
	fclose(fsession);
}

void score_write(int ndefused, int cols, int rows)
{
	FILE *scorelog = fopen(SCORE_LOG_PATH, "a");
	char *playername = get_pname();
	if (scorelog == NULL)
	{
		mvprintw(0, 0, "Error opening file, exiting...");
		refresh();
		exit(EXIT_FAILURE);
	}
	else
	{
		fprintf(scorelog, "%s,%d,%dx%d\n", playername, ndefused, cols, rows);
		sort_scorelog(scorelog); // pending
		clrtoeol();
		show_scorelog(scorelog);
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

void show_scorelog(FILE *scorelog)
{

}

void parse_data(FILE *scorelog)
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

void game_over(WINDOW *gamew, int ymid, int xmid)
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
