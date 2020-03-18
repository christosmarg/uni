#include "minesweeper.h"
#include <pthread.h>

int main(int argc, char **argv)
{	
	main_win();
	options_menu();

	int yMax, xMax;
	WINDOW *menuWin = menu_win(&yMax, &xMax);
	int COLS = set_cols(menuWin, xMax);
	int ROWS = set_rows(menuWin, yMax);
	int NMINES = set_nmines(menuWin, COLS*ROWS);

	WINDOW *gameWin = game_win(COLS, ROWS, NMINES);
	char **dispboard = init_dispboard(gameWin, COLS, ROWS);
	char **mineboard = init_mineboard(gameWin, COLS, ROWS, NMINES);
	
	pthread_t audioThread;
	long threadID = 1;
	pthread_create(&audioThread, NULL, play_audio, (void *)threadID);
	play_minesweeper(gameWin, dispboard, mineboard, COLS, ROWS, NMINES);
	
	pthread_cancel(audioThread);
	free(dispboard);
	free(mineboard);
	endwin();

	return 0;
}
