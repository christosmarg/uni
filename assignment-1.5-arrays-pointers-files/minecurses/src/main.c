#include "minesweeper.h"
#include <pthread.h>

int main(int argc, char **argv)
{	
	init_curses();
	echo();
	int COLS = set_cols();
	int ROWS = set_rows();
	int NMINES = set_nmines(COLS*ROWS);
	noecho();
	options_menu();
	erase();
	refresh();

	WINDOW *gamew = game_win(COLS, ROWS, NMINES);
	char **dboard = init_dboard(gamew, COLS, ROWS);
	char **mboard = init_mboard(gamew, COLS, ROWS, NMINES);
	
	pthread_t audiothread;
	long threadid = 1;
	pthread_create(&audiothread, NULL, play_audio, (void *)threadid);
	play_minesweeper(gamew, dboard, mboard, COLS, ROWS, NMINES);
	
	pthread_cancel(audiothread);
	free(dboard);
	free(mboard);
	endwin();

	return 0;
}
