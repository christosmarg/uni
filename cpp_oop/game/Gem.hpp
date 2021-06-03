#ifndef _GEM_HPP_
#define _GEM_HPP_

class Gem {
private:
	int x;
	int y;
	char sym;

public:
	Gem(int x, int y, char sym);

	int get_x() const;
	int get_y() const;
	char get_sym() const;
};

#endif /* _GEM_HPP_ */
