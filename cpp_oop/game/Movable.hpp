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
	int get_x() const;
	int get_y() const;
	int get_dir() const;
	char get_sym() const;
};

#endif /* _MOVABLE_HPP_ */
