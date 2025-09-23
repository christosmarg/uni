#include "Movable.hpp"

Movable::Movable()
{
}

Movable::Movable(int x, int y, int dir, char sym)
	:x(x), y(y), dir(dir), sym(sym)
{
}

Movable::~Movable()
{
}

void
Movable::set_newpos(int dir, int xmax, int ymax)
{
	switch (dir) {
	case Direction::LEFT:
		if (--x < 0)
			x = 0;
		break;
	case Direction::RIGHT:
		if (++x > xmax - 1)
			x = xmax - 1;
		break;
	case Direction::UP:
		if (--y < 2)
			y = 2;
		break;
	case Direction::DOWN:
		if (++y > ymax - 1)
			y = ymax - 1;
		break;
	}
}

int
Movable::get_x()
{
	return x;
}

int
Movable::get_y()
{
	return y;
}

char
Movable::get_sym()
{
	return sym;
}
