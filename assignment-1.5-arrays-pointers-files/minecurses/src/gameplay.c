#include "gameplay.h"
#include "main.h"

void
play(WINDOW *gw, Board *b)
{
	int mbx = 0, mby = 0;
	int gameover = FALSE;
	int ndefused = 0;
	int move;

	do
	{
		erase();
		delwin(gw);
		refresh();
		gw = game_win(b->rows, b->cols);
		print_board(gw, b);
		session_info(mbx, mby, ndefused, b->nmines);
		navigate(gw, &move, &mbx, &mby);
		switch (move)
		{
			case ENTER: case OPEN_LOWER: case OPEN_UPPER:
				gameover = open_cell(gw, b, mby, mbx, gameover);
				break;
			case FLAG_LOWER: case FLAG_UPPER:
				handle_flags(gw, b, mby, mbx);
				break;
			case DEFUSE_LOWER: case DEFUSE_UPPER:
				if (b->db[mby][mbx] == FLAG && b->mb[mby][mbx] == MINE)
				{
					ndefused++;
					defuse_mine(gw, b, mby, mbx);
				}
				else if (b->db[mby][mbx] == FLAG && b->mb[mby][mbx] != MINE) gameover = TRUE;              
				break;
			case PAUSE_AUDIO:
				pause_audio();
				break;
			case VOLUME_UP: case VOLUME_DOWN:
				volume(move);
				break;
			case 'm':
				handle_menu(gw, b);
				break;
			case 'r':
				clear_board(b);
				reset(b);
				init_game(gw, b);
				break;
			default: break;
		}
	} while (((mby >= 0 && mby < b->rows) && (mbx >= 0 && mbx < b->cols)) &&
			 ndefused < b->nmines && !gameover && move != QUIT);	

	if (gameover)
		handle_gameover(gw, b, mby, mbx);
	if (ndefused == b->nmines)
		handle_win(gw, b, mby, mbx, ndefused);
}

int
open_cell(WINDOW *gw, Board *b, int mby, int mbx, int gameover)
{
	transfer(b, mby, mbx);
	reveal(gw, b, mby, mbx, mby+1, 3*mbx+2);
	if (b->db[mby][mbx] == MINE) gameover = TRUE;
	return gameover;
}

void
handle_flags(WINDOW *gw, Board *b, int mby, int mbx)
{
	if (b->db[mby][mbx] == FLAG) b->db[mby][mbx] = BLANK;
	else if (b->db[mby][mbx] != FLAG && b->db[mby][mbx] != BLANK) return;
	else b->db[mby][mbx] = FLAG;
	reveal(gw, b, mby, mbx, mby+1, 3*mbx+2);
}

void
defuse_mine(WINDOW *gw, Board *b, int mby, int mbx)
{
	refresh();
	b->db[mby][mbx] = b->mb[mby][mbx] = DEFUSED;
	reveal(gw, b, mby, mbx, mby+1, 3*mbx+2);
}

void
transfer(Board *b, int mby, int mbx)
{
	b->db[mby][mbx] = b->mb[mby][mbx];
}

void
reveal(WINDOW *gw, Board *b, int mby, int mbx, int y, int x)
{
	mvwaddch(gw, y, x, b->db[mby][mbx]);
	wrefresh(gw);
}

int
is_defused(Board *b, int mby, int mbx)
{
	return (b->db[mby][mbx] == DEFUSED) ? TRUE : FALSE;
}

void
handle_menu(WINDOW *gw, Board *b)
{
	options_menu();
	box(gw, 0, 0);
	print_board(gw, b);
}

void
handle_gameover(WINDOW *gw, Board *b, int mby, int mbx)
{
	game_over(gw);
	getchar();
	erase();
	refresh();
	box(gw, 0, 0);
	print_board(gw, b);
	wrefresh(gw);
	session_write(b, mbx, mby, GAME_LOST);
}

void
handle_win(WINDOW *gw, Board *b, int mby, int mbx, int ndefused)
{
	game_won(gw);
	getchar();
	session_write(b, mbx, mby, GAME_WON);
	score_write(ndefused, b->rows, b->cols);
}
