#include "audio.h"
#include "gameplay.h"
#include "main.h"
#include "minesweeper.h"
#include "settings.h"
#include "wins.h"
#include <pthread.h>

static void clear_board(Board *brd)
{
	int i;
	for (i = 0; i < brd->rows; i++)
	{
		free(brd->db[i]);
		free(brd->mb[i]);
	}
	free(brd->db);
	free(brd->mb);
}

int main(int argc, char **argv)
{	
	Board brd;
	init_curses();
	echo();
	brd.cols = set_cols();
	brd.rows = set_rows();
	brd.nmines = set_nmines(brd.rows * brd.cols);
	noecho();
	options_menu();
	erase();
	refresh();

	WINDOW *gamew = game_win(brd.rows, brd.cols);
	brd.db = init_dboard(gamew, brd.cols, brd.rows);
	brd.mb = init_mboard(gamew, brd.cols, brd.rows, brd.nmines);
	
	pthread_t audiothread;
	long threadid = 1;
	pthread_create(&audiothread, NULL, play_audio, (void *)threadid);
	play_minesweeper(gamew, &brd);
	
	pthread_cancel(audiothread);
	clear_board(&brd);
	delwin(gamew);
	endwin();

	return 0;
}
