#ifndef _GNOME_HPP_
#define _GNOME_HPP_

#include "Movable.hpp"

class Gnome: public Movable {
public:
	Gnome(int x, int y, int dir, char sym);
};

#endif /* _GNOME_HPP_ */
