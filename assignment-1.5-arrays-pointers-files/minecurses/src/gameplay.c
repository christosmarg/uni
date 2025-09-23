#include "gameplay.h"

void play_minesweeper(WINDOW *gamew, Board *brd)
{
	int mbx = 0, mby = 0;
	int gameover = FALSE;
	int ndefused = 0;
	int ymid, xmid;
	char move;
	ymid = YMAX/2;
	xmid = XMAX/2;

	do
	{
		erase();
		delwin(gamew);
		refresh();
		gamew = game_win(brd->rows, brd->cols);
		print_board(gamew, brd);
		session_info(mbx, mby, xmid, ndefused, brd->nmines);
		navigate(gamew, &move, &mbx, &mby);
		switch (move)
		{
			case ENTER: case OPEN_LOWER: case OPEN_UPPER:
				gameover = open_cell(gamew, brd, mby, mbx, gameover);
				break;
			case FLAG_LOWER: case FLAG_UPPER:
				handle_flags(gamew, brd, mby, mbx);
				break;
			case DEFUSE_LOWER: case DEFUSE_UPPER:
				if (brd->db[mby][mbx] == FLAG && brd->mb[mby][mbx] == MINE)
				{
					ndefused++;
					defuse_mine(gamew, brd, mby, mbx);
				}
				else if (brd->db[mby][mbx] == FLAG && brd->mb[mby][mbx] != MINE) gameover = TRUE;              
				break;
			case PAUSE_AUDIO:
				pause_audio();
				break;
			case VOLUME_UP: case VOLUME_DOWN:
				volume(move);
				break;
			case 'm':
				handle_menu(gamew, brd);
				break;
			default: break;
		}
	} while (((mby >= 0 && mby < brd->rows) && (mbx >= 0 && mbx < brd->cols)) &&
			 ndefused < brd->nmines && !gameover && move != QUIT);	

	if (gameover)
		handle_gameover(gamew, brd, ymid, xmid, mby, mbx);
	if (ndefused == brd->nmines)
		handle_win(gamew, brd, ymid, xmid, mby, mbx, ndefused);
}

int open_cell(WINDOW *gamew, Board *brd, int mby, int mbx, int gameover)
{
	transfer(brd, mby, mbx);
	reveal(gamew, brd, mby, mbx, mby+1, 3*mbx+2);
	if (brd->db[mby][mbx] == MINE) gameover = TRUE;
	return gameover;
}

void handle_flags(WINDOW *gamew, Board *brd, int mby, int mbx)
{
	if (brd->db[mby][mbx] == FLAG) brd->db[mby][mbx] = BLANK;
	else if (brd->db[mby][mbx] != FLAG && brd->db[mby][mbx] != BLANK) return;
	else brd->db[mby][mbx] = FLAG;
	reveal(gamew, brd, mby, mbx, mby+1, 3*mbx+2);
}

void defuse_mine(WINDOW *gamew, Board *brd, int mby, int mbx)
{
	refresh();
	brd->db[mby][mbx] = brd->mb[mby][mbx] = DEFUSED;
	reveal(gamew, brd, mby, mbx, mby+1, 3*mbx+2);
}

void transfer(Board *brd, int mby, int mbx)
{
	brd->db[mby][mbx] = brd->mb[mby][mbx];
}

void reveal(WINDOW *gamew, Board *brd, int mby, int mbx, int y, int x)
{
	mvwaddch(gamew, y, x, brd->db[mby][mbx]);
	wrefresh(gamew);
}

int is_defused(Board *brd, int mby, int mbx)
{
	return (brd->db[mby][mbx] == DEFUSED) ? TRUE : FALSE;
}

void handle_menu(WINDOW *gamew, Board *brd)
{
	options_menu();
	box(gamew, 0, 0);
	print_board(gamew, brd);
}

void handle_gameover(WINDOW *gamew, Board *brd, int ymid, int xmid, int mby, int mbx)
{
	game_over(gamew, ymid, xmid);
	getchar();
	erase();
	refresh();
	box(gamew, 0, 0);
	print_board(gamew, brd);
	wrefresh(gamew);
	session_write(brd, mbx, mby, "lost");
}

void handle_win(WINDOW *gamew, Board *brd, int ymid, int xmid, int mby, int mbx, int ndefused)
{
	game_won(gamew, ymid, xmid);
	getchar();
	session_write(brd, mbx, mby, "won");
	score_write(ndefused, brd->rows, brd->cols);
}
