#include "audio.h"
#include "gameplay.h"
#include "main.h"
#include "minesweeper.h"
#include "settings.h"
#include "wins.h"
#include <pthread.h>

int
main(int argc, char **argv)
{	
	init_curses();
	Board b;
	reset(&b);
	WINDOW *gw = game_win(b.rows, b.cols);
	init_game(gw, &b);

	pthread_t audiothread;
	long threadid = 1;
	pthread_create(&audiothread, NULL, play_audio, (void *)threadid);
	play(gw, &b);
	
	pthread_cancel(audiothread);
	clear_board(&b);
	delwin(gw);
	endwin();

	return 0;
}

void
reset(Board *b)
{
	echo();
	b->cols = set_cols();
	b->rows = set_rows();
	b->nmines = set_nmines(b->rows * b->cols);
	noecho();
	options_menu();
	erase();
	refresh();
}

void
init_game(WINDOW *gw, Board *b)
{
	init_db(gw, b);
	init_mb(gw, b);
}

void
clear_board(Board *b)
{
	int i;
	for (i = 0; i < b->rows; i++)
	{
		free(b->db[i]);
		free(b->mb[i]);
	}
	free(b->db);
	free(b->mb);
}
