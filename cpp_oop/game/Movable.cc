#include "Movable.hpp"

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
		if (++x > xmax - 2)
			x = xmax - 2;
		break;
	case Direction::UP:
		if (--y < 0)
			y = 0;
		break;
	case Direction::DOWN:
		if (++y > ymax - 1)
			y = ymax - 1;
		break;
	}
	this->dir = dir;
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

int
Movable::get_dir()
{
	return dir;
}

char
Movable::get_sym()
{
	return sym;
}
