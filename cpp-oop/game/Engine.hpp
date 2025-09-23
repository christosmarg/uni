#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <cmath>
#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <ncurses.h>

#include "Gnome.hpp"
#include "Potter.hpp"
#include "Traal.hpp"
#include "Score.hpp"

#ifndef ESC
#define ESC 27
#endif /* ESC */

#define CENTER(x, y) (((x) >> 1) - ((y) >> 1))

class Engine {
private:

	std::vector<Movable *> entities;
	std::vector<std::vector<char>> map;
	std::vector<int> colors;
	Potter *player;
	Score *score;
	WINDOW *gw;
	int xmax;
	int ymax;
	int wxmax;
	int wymax;
	int w;
	int h;
	int nenemies = 5;
	volatile sig_atomic_t f_running;

public:
	explicit Engine(const char *mapfile, const char *scorefile);
	~Engine();

	void kbd_input();
	void enemies_move();
	void collisions();
	void upd_score();
	void redraw();
	bool is_running();

private:
	bool load_map(const char *mapfile);
	bool init_curses();
	void calc_pos(int *x, int *y);
	bool init_entities();
	bool init_score(const char *scorefile);
	bool collides_with_wall(int x, int y);
	void ctrl_menu();
	void calc_dist(std::map<int, int>& dists, int ex, int ey, int dir);
};

#endif /* _ENGINE_HPP_ */
