#include "gameplay.h"
#include "main.h"

#define X b->x
#define Y b->y

void
play(Board *b)
{
	b->x = b->y = 0;
	b->gameover = FALSE;
	b->ndefused = 0;
	int move;

	do
	{
		erase();
		delwin(b->gw);
		refresh();
		b->gw = game_win(b->rows, b->cols);
		print_board(b);
		session_info(b);
		navigate(b, &move);
		switch (move)
		{
			case ENTER:			/* FALLTHROUGH */
			case OPEN_LOWER:
			case OPEN_UPPER:
				b->gameover = open_cell(b);
				break;
			case FLAG_LOWER:	/* FALLTHROUGH */
			case FLAG_UPPER:
				handle_flags(b);
				break;
			case DEFUSE_LOWER:	/* FALLTHROUGH */
			case DEFUSE_UPPER:
				if (b->db[Y][X] == FLAG && b->mb[Y][X] == MINE)
				{
					b->ndefused++;
					defuse_mine(b);
				}
				else if (b->db[Y][X] == FLAG && b->mb[Y][X] != MINE)
					b->gameover = TRUE;              
				break;
			case PAUSE_AUDIO:
				pause_audio();
				break;
			case VOLUME_UP:		/* FALLTHROUGH */
			case VOLUME_DOWN:
				volume(move);
				break;
			case 'm':
				handle_menu(b);
				break;
			case 'r':
				clear_board(b);
				reset(b);
				init_game(b);
				break;
			default: break;
		}
	} while (((Y >= 0 && Y < b->rows) &&
			(X >= 0 && X < b->cols))  &&
			b->ndefused < b->nmines && !b->gameover &&
			move != QUIT);	

	if (b->gameover)
		handle_gameover(b);
	if (b->ndefused == b->nmines)
		handle_win(b);
}

int
open_cell(Board *b)
{
	transfer(b);
	reveal(b);
	return (b->db[Y][X] == MINE) ? TRUE : FALSE;
}

void
handle_flags(Board *b)
{
	if (b->db[Y][X] == FLAG)
		b->db[Y][X] = BLANK;
	else if (b->db[Y][X] != FLAG &&
			 b->db[Y][X] != BLANK)
		return;
	else b->db[Y][X] = FLAG;
	reveal(b);
}

void
defuse_mine(Board *b)
{
	refresh();
	b->db[Y][X] = b->mb[Y][X] = DEFUSED;
	reveal(b);
}

void
transfer(Board *b)
{
	b->db[Y][X] = b->mb[Y][X];
}

void
reveal(const Board *b)
{
	int y = b->y + 1;
	int x = 3 * b->x + 2;
	mvwaddch(b->gw, y, x, b->db[Y][X]);
	wrefresh(b->gw);
}

int
is_defused(const Board *b)
{
	return (b->db[Y][X] == DEFUSED) ? TRUE : FALSE;
}

void
handle_menu(const Board *b)
{
	options_menu();
	box(b->gw, 0, 0);
	print_board(b);
}

void
handle_gameover(const Board *b)
{
	game_over(b);
	getchar();
	erase();
	refresh();
	box(b->gw, 0, 0);
	print_board(b);
	wrefresh(b->gw);
	session_write(b, GAME_LOST);
}

void
handle_win(const Board *b)
{
	game_won(b);
	getchar();
	session_write(b, GAME_WON);
	score_write(b);
}

#undef Y
#undef X
