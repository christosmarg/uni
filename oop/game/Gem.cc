#include "Gem.hpp"

Gem::Gem(int x, int y, char sym)
	:x(x), y(y), sym(sym)
{
}

int
Gem::get_x() const
{
	return x;
}

int
Gem::get_y() const
{
	return y;
}

char
Gem::get_sym() const
{
	return sym;
}
