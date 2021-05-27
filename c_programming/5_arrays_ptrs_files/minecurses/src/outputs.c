#include "outputs.h"

void
print_board(const Board *b)
{    
	int i, j, x, y = 1;
	print_grid(b);
	wattron(b->gw, A_BOLD);
	for (i = 0; i < b->rows; i++)
	{
		x = 2; 
		for (j = 0; j < b->cols; j++)
		{
			mvwaddch(b->gw, y, x, b->db[i][j]);
			x += 3;
		}
		y++;
	}
}

void
print_grid(const Board *b)
{
	int i, j;
	wattroff(b->gw, A_BOLD);
	for (i = 1; i <= b->rows; i++)
	{
		wmove(b->gw, i, 1);
		for (j = 0; j < b->cols; j++)
			wprintw(b->gw, "[ ]");
	}
	wrefresh(b->gw);
}

#define YMID(x) getmaxy(x)/2
#define XMID(x) getmaxx(x)/2

void
session_info(const Board *b)
{
	mvprintw(0, 0, "Current position: (%d, %d) ", b->x, b->y);
	mvprintw(0, XMID(stdscr)-strlen("Defused mines: x/x")/2,
			"Defused mines: %d/%d", b->ndefused, b->nmines);
	mvprintw(0, XMAX(stdscr)-strlen("m Controls"), "m Controls");
}

void
session_write(const Board *b, State state)
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
		state == GAME_WON
			? fprintf(fsession, "Mine hit at position (%d, %d)\n\n",
					b->x+1, b->y+1)
			: fprintf(fsession, "Last mine defused at position (%d, %d)\n\n",
					b->x+1, b->y+1);
		fprintf(fsession, "Board overview\n\n");
		for (i = 0; i < b->rows; i++)
		{
			for (j = 0; j < b->cols; j++)
				fprintf(fsession, "%c ", b->mb[i][j]);
			fprintf(fsession, "\n");
		}           
	}
	fclose(fsession);
}

void
score_write(const Board *b)
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
		fprintf(scorelog, "%s,%d,%dx%d\n",
				playername, b->ndefused, b->cols, b->rows);
		sort_scorelog(scorelog);
		clrtoeol();
		show_scorelog(scorelog);
		mvprintw(0, 0, "New score written to score log");
		refresh();
		getchar();
	}
	fclose(scorelog);
	free(playername);
}

char *
get_pname(void)
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

void
sort_scorelog(FILE *scorelog)
{

}

void
show_scorelog(FILE *scorelog)
{

}

void
parse_data(FILE *scorelog)
{

}

void
game_won(const Board *b)
{
	wclear(b->gw);
	wrefresh(b->gw);
	attron(A_BOLD);
	mvprintw(YMID(stdscr)-2, XMID(stdscr)-11, "You defused all the mines!");
	mvprintw(YMID(stdscr)-1, XMID(stdscr)-3, "You won :)");
	mvprintw(YMID(stdscr), XMID(stdscr)-11, "Press any key to continue");
	refresh();
	attroff(A_BOLD);
}

void
game_over(const Board *b)
{
	wclear(b->gw);
	wrefresh(b->gw);
	attron(A_BOLD);
	mvprintw(YMID(stdscr)-2, XMID(stdscr)-24, "You hit a mine! (or tried to defuse the wrong cell)");
	mvprintw(YMID(stdscr)-1, XMID(stdscr)-4, "Game over :(");
	mvprintw(YMID(stdscr), XMID(stdscr)-11, "Press any key to continue");
	refresh();
	attroff(A_BOLD);
}

#undef YMID
#undef XMID
