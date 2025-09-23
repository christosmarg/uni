#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <ncurses.h>

#include "Gnome.hpp"
#include "Potter.hpp"
#include "Traal.hpp"
#include "Score.hpp"

class Engine {
private:

	std::vector<Movable *> entities;
	std::vector<std::vector<char>> map;
	std::vector<int> colors;
	Potter *player;
	Score score;
	int xmax;
	int ymax;
	int f_running;

public:
	Engine();
	~Engine();

	void init(const char *mapfile, const char *scorefile);
	void kbd_input();
	void collisions();
	void upd_score();
	void redraw();
	bool is_running();

private:
	bool load_map(const char *mapfile);
	bool init_curses();
	bool init_entities();
	bool init_score(const char *scorefile);
};

#endif /* _ENGINE_HPP_ */
