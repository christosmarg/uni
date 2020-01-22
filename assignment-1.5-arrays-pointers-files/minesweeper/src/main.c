#include "minesweeper.h"

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
    play_minesweeper(gameWin, dispboard, mineboard, COLS, ROWS, NMINES);

    free(dispboard);
    free(mineboard);
	
	endwin();

	return 0;
}
