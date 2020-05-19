#include "navigation.h"

void
navigate(WINDOW *gw, int *mv, int *mbx, int *mby)
{
	static int y = 1, x = 2;
	update_curs(gw, y, x);
	*mbx = (x-2)/3;
	*mby = y-1;
	refresh();
	getmv(gw, mv, &y, &x);
}

void
getmv(WINDOW *gw, int *mv, int *y, int *x)
{
	*mv = wgetch(gw);
	switch (*mv) // vim keys support!!
	{
		case 'k': case 'K':
		case 'w': case 'W':
			mvup(y);
			break;
		case 'j': case 'J':
		case 's': case 'S':
			mvdown(y, YMAX(gw));
			break;
		case 'h': case 'H':
		case 'a': case 'A':
			mvleft(x);
			break;
		case 'l': case 'L':
		case 'd': case 'D':
			mvright(x, XMAX(gw));
			break;
	}
}

void
mvup(int *y)
{
	(*y)--;
	if (*y < 1) *y = 1;
}

void
mvdown(int *y, int ymax)
{
	(*y)++;
	if (*y > ymax-2) *y = ymax-2;
}

void
mvleft(int *x)
{
	*x -= 3;
	if (*x < 2) *x = 2;
}

void
mvright(int *x, int xmax)
{
	*x += 3;
	if (*x > xmax-3) *x = xmax-3;
}

void
update_curs(WINDOW *gw, int y, int x)
{
	wmove(gw, y, x);
}
