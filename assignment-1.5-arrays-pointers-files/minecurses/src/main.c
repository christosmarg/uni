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
#ifndef NCURSES_VERSION
	fprintf(stderr, "ncurses is needed in order to run this program.\n");
	return EXIT_FAILURE;
#endif /* NCURSES_VERSION */
	init_curses();
	Board b;
	reset(&b);
	b.gw = game_win(b.rows, b.cols);
	init_game(&b);

	pthread_t audiothread;
	long tid = 1;
	pthread_create(&audiothread, NULL, play_audio, (void *)tid);
	play(&b);
	
	pthread_cancel(audiothread);
	clear_board(&b);
	delwin(b.gw);
	endwin();
	return EXIT_SUCCESS;
}

void
reset(Board *b)
{
	echo();
	b->cols		= set_cols();
	b->rows		= set_rows();
	b->nmines	= set_nmines(b->rows * b->cols);
	b->ndefused = b->x = b->y = 0;
	b->gameover = FALSE;
	noecho();
	options_menu();
	erase();
	refresh();
}

void
init_game(Board *b)
{
	init_db(b);
	init_mb(b);
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
