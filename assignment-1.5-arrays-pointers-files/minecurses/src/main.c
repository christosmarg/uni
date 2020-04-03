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
	char **dispboard = init_dispboard(gamew, COLS, ROWS);
	char **mineboard = init_mineboard(gamew, COLS, ROWS, NMINES);
	
	pthread_t audioThread;
	long threadID = 1;
	pthread_create(&audioThread, NULL, play_audio, (void *)threadID);
	play_minesweeper(gamew, dispboard, mineboard, COLS, ROWS, NMINES);
	
	pthread_cancel(audioThread);
	free(dispboard);
	free(mineboard);
	endwin();

	return 0;
}
