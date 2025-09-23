#include "audio.h"
#include "gameplay.h"
#include "main.h"
#include "minesweeper.h"
#include "settings.h"
#include "wins.h"
#include <pthread.h>

int main(int argc, char **argv)
{	
	Board brd;
	init_curses();
	reset(&brd);
	WINDOW *gamew = game_win(brd.rows, brd.cols);
	init_game(gamew, &brd);
	pthread_t audiothread;
	long threadid = 1;
	pthread_create(&audiothread, NULL, play_audio, (void *)threadid);
	play(gamew, &brd);
	
	pthread_cancel(audiothread);
	clear_board(&brd);
	delwin(gamew);
	endwin();

	return 0;
}

void reset(Board *brd)
{
	echo();
	brd->cols = set_cols();
	brd->rows = set_rows();
	brd->nmines = set_nmines(brd->rows * brd->cols);
	noecho();
	options_menu();
	erase();
	refresh();
}

void init_game(WINDOW *gamew, Board *brd)
{
	brd->db = init_db(gamew, brd->cols, brd->rows);
	brd->mb = init_mb(gamew, brd->cols, brd->rows, brd->nmines);
}

void clear_board(Board *brd)
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
