#ifndef _MOVABLE_HPP_
#define _MOVABLE_HPP_

class Movable {
protected:
	int x;
	int y;
	int dir;
	char sym;

public:
	enum Direction { LEFT, RIGHT, UP, DOWN };

public:
	explicit Movable(int x, int y, int dir, char sym);
	virtual ~Movable();

	void set_newpos(int dir, int xmax, int ymax);
	int get_x();
	int get_y();
	char get_sym();
};

#endif /* _MOVABLE_HPP_ */
