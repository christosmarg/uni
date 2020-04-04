#include "minesweeper.h"
#include <pthread.h>

int main(int argc, char **argv)
{	
	main_win();
	options_menu();

	int ymax, xmax;
	WINDOW *menuw = menu_win(&ymax, &xmax);
	int COLS = set_cols(menuw, xmax);
	int ROWS = set_rows(menuw, ymax);
	int NMINES = set_nmines(menuw, COLS*ROWS);

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
