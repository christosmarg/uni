#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_

#include <algorithm>
#include <cmath>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <ncurses.h>

#include "Gem.hpp"
#include "Gnome.hpp"
#include "Potter.hpp"
#include "Traal.hpp"
#include "Score.hpp"

#ifndef ESC
#define ESC 27
#endif /* ESC */

#define CENTER(x, y) (((x) >> 1) - ((y) >> 1))

#define SYM_WALL '*'
#define SYM_PATH ' '
#define SYM_POTTER 'P'
#define SYM_GNOME 'G'
#define SYM_TRAAL 'T'
#define SYM_STONE '+'
#define SYM_PARCHMENT 'O'

class Engine {
private:

	std::vector<Movable *> entities;
	std::vector<Gem *> gems;
	std::vector<std::string> map;
	std::vector<int> colors;
	std::vector<std::string> ctrls;
	std::vector<std::string> rules;
	Potter *player;
	Score *score;
	Gem *prch;
	WINDOW *gw;
	int xmax;
	int ymax;
	int wxmax;
	int wymax;
	int w;
	int h;
	int nenemies = 2;
	int ngems = 10;
	volatile sig_atomic_t f_running;

public:
	explicit Engine(const char *mapfile, const char *scorefile);
	~Engine();

	void kbd_input();
	void enemies_move();
	void collisions();
	void redraw() const;
	bool is_running() const;

private:
	bool init_curses();
	bool init_gamewin();
	void load_map(const char *mapfile);
	void calc_pos(int *x, int *y);
	void init_entities();
	void spawn_parchment();
	bool collides_with_wall(int x, int y) const;
	void popup(const std::vector<std::string>& lines) const;
	void calc_dist(std::map<int, int>& dists, int ex, int ey, int dir) const;
	void upd_score(int n);
	void draw_map() const;
	void draw_entities() const;
	void draw_gems() const;
	void draw_parchment() const;
};

#endif /* _ENGINE_HPP_ */
