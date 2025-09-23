#include "gameplay.h"

void play_minesweeper(WINDOW *gamew, char **dboard, char **mboard, int COLS, int ROWS, int NMINES)
{
    int mbx = 0, mby = 0;
    int gameover = FALSE;
    int ndefused = 0;
    int ymax, xmax, ymid, xmid;
    char move;
    getmaxyx(stdscr, ymax, xmax);
    ymid = ymax/2;
    xmid = xmax/2;
	print_board(gamew, dboard, COLS, ROWS);

    do
    {
		session_info(mbx, mby, xmax, xmid, ndefused, NMINES);
        navigate(gamew, dboard, &move, &mbx, &mby);
		switch (move)
		{
			case ENTER: case OPEN_LOWER: case OPEN_UPPER:
				gameover = open_cell(gamew, dboard, mboard, mby, mbx, gameover);
				break;
			case FLAG_LOWER: case FLAG_UPPER:
				handle_flags(gamew, dboard, mboard, mby, mbx);
				break;
			case DEFUSE_LOWER: case DEFUSE_UPPER:
				if (dboard[mby][mbx] == FLAG && mboard[mby][mbx] == MINE)
				{
					ndefused++;
					defuse_mine(gamew, dboard, mboard, mby, mbx);
				}
				else if (dboard[mby][mbx] == FLAG && mboard[mby][mbx] != MINE) gameover = TRUE;              
				break;
			case PAUSE_AUDIO:
				pause_audio();
				break;
			case VOLUME_UP: case VOLUME_DOWN:
				volume(move);
				break;
			case 'm':
				handle_menu(gamew, dboard, COLS, ROWS);
				break;
			default: break;
		}
    } while (((mby >= 0 && mby < ROWS) && (mbx >= 0 && mbx < COLS)) &&
             ndefused < NMINES && !gameover && move != QUIT);	

    if (gameover)
		handle_gameover(gamew, mboard, ymid, xmid, COLS, ROWS, mby, mbx);
    if (ndefused == NMINES)
		handle_win(gamew, mboard, ymid, xmid, COLS, ROWS, mby, mbx, ndefused);
}

int open_cell(WINDOW *gamew, char **dboard, char **mboard, int mby, int mbx, int gameover)
{
	transfer(dboard, mboard, mby, mbx);
	reveal(gamew, dboard, mby, mbx, mby+1, 3*mbx+2);
	if (dboard[mby][mbx] == MINE) gameover = TRUE;
	return gameover;
}

void handle_flags(WINDOW *gamew, char **dboard, char **mboard, int mby, int mbx)
{
	if (dboard[mby][mbx] == FLAG) dboard[mby][mbx] = BLANK;
	else if (dboard[mby][mbx] != FLAG && dboard[mby][mbx] != BLANK) return;
	else dboard[mby][mbx] = FLAG;
	reveal(gamew, dboard, mby, mbx, mby+1, 3*mbx+2);
}

void defuse_mine(WINDOW *gamew, char **dboard, char **mboard, int mby, int mbx)
{
	refresh();
	dboard[mby][mbx] = mboard[mby][mbx] = DEFUSED;
	reveal(gamew, dboard, mby, mbx, mby+1, 3*mbx+2);
}

void transfer(char **dboard, char **mboard, int mby, int mbx)
{
    dboard[mby][mbx] = mboard[mby][mbx];
}

void reveal(WINDOW *gamew, char **dboard, int mby, int mbx, int y, int x)
{
    mvwaddch(gamew, y, x, dboard[mby][mbx]);
    wrefresh(gamew);
}

int is_defused(char **dboard, char **mboard, int mby, int mbx)
{
    return ((dboard[mby][mbx] == DEFUSED)) ? TRUE : FALSE;
}

void handle_menu(WINDOW *gamew, char **dboard, int COLS, int ROWS)
{
	options_menu();
	box(gamew, 0, 0);
	print_board(gamew, dboard, COLS, ROWS);
}

void handle_gameover(WINDOW *gamew, char **mboard, int ymid, int xmid, int COLS, int ROWS, int mby, int mbx)
{
	game_over(gamew, mboard, ymid, xmid);
	getchar();
	erase();
	refresh();
	box(gamew, 0, 0);
	print_board(gamew, mboard, COLS, ROWS);
	wrefresh(gamew);
	session_write(mboard, COLS, ROWS, mbx, mby, "lost");
}

void handle_win(WINDOW *gamew, char **mboard, int ymid, int xmid, int COLS, int ROWS, int mby, int mbx, int ndefused)
{
	game_won(gamew, ymid, xmid);
	getchar();
	session_write(mboard, COLS, ROWS, mbx, mby, "won");
	score_write(ndefused, COLS, ROWS);
}
