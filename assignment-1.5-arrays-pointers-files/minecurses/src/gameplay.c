#include "gameplay.h"

void play_minesweeper(WINDOW *gamew, char **dboard, char **mboard, int COLS, int ROWS, int NMINES)
{
    int mbx = 0, mby = 0;
    bool gameover = false;
    int ndefused = 0;
    int ymax, xmax, ymid, xmid;
    char move;
    getmaxyx(stdscr, ymax, xmax);
    ymid = ymax/2;
    xmid = xmax/2;

	print_board(gamew, dboard, COLS, ROWS);
    
    do
    {
        navigate(gamew, dboard, &move, &mbx, &mby);
        
		if (move == ENTER || move == OPEN_LOWER || move == OPEN_UPPER) // handle cell opening
			gameover = open_cell(gamew, dboard, mboard, mby, mbx, gameover);
        else if (move == FLAG_LOWER || move == FLAG_UPPER) // handle falgs
			handle_flags(gamew, dboard, mboard, mby, mbx);
        else if (move == DEFUSE_LOWER || move == DEFUSE_UPPER) // check for defuse
        {
			if (dboard[mby][mbx] == FLAG && mboard[mby][mbx] == MINE)
            {
				ndefused++;
				defuse_mine(gamew, dboard, mboard, mby, mbx);
            }
            else if (dboard[mby][mbx] == FLAG && mboard[mby][mbx] != MINE) gameover = true;              
        }
        else if (move == PAUSE_AUDIO) pause_audio(); // handle audio
        else if (move == VOLUME_UP || move == VOLUME_DOWN) volume(move);

        mvprintw(1, xmid-8, "Defused mines: %d/%d", ndefused, NMINES);
        
    } while (((mby >= 0 && mby < ROWS) && (mbx >= 0 && mbx < COLS)) &&
             ndefused < NMINES && !gameover && move != QUIT);	

    if (gameover == true)
		handle_gameover(gamew, mboard, ymid, xmid, COLS, ROWS, mby, mbx);
    if (ndefused == NMINES)
		handle_win(gamew, mboard, ymid, xmid, COLS, ROWS, mby, mbx, ndefused);
}

bool open_cell(WINDOW *gamew, char **dboard, char **mboard, int mby, int mbx, bool gameover)
{
	transfer(dboard, mboard, mby, mbx);
	reveal(gamew, dboard, mby, mbx, mby+1, 3*mbx+2);
	if (dboard[mby][mbx] == MINE) gameover = true;
	return gameover;
}

void handle_flags(WINDOW *gamew, char **dboard, char **mboard, int mby, int mbx)
{
	if (dboard[mby][mbx] == FLAG) dboard[mby][mbx] = BLANK; // undo flag 
	else if (dboard[mby][mbx] != FLAG && dboard[mby][mbx] != BLANK) return; // dont flag an already opened mine
	else dboard[mby][mbx] = FLAG; // flag if not flagged already
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

bool is_defused(char **dboard, char **mboard, int mby, int mbx)
{
    return ((dboard[mby][mbx] == DEFUSED)) ? true : false;
}

void handle_gameover(WINDOW *gamew, char **mboard, int ymid, int xmid, int COLS, int ROWS, int mby, int mbx)
{
	game_over(gamew, mboard, ymid, xmid);
	getchar();
	print_board(gamew, mboard, COLS, ROWS);
	session_write(mboard, COLS, ROWS, mbx, mby, "lost");
}

void handle_win(WINDOW *gamew, char **mboard, int ymid, int xmid, int COLS, int ROWS, int mby, int mbx, int ndefused)
{
	game_won(gamew, ymid, xmid);
	getchar();
	session_write(mboard, COLS, ROWS, mbx, mby, "won");
	score_write(ndefused, COLS, ROWS);
}
