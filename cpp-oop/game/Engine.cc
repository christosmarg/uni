#include "Engine.hpp"

enum Color {
	WALL = 1,
	PATH,
	POTTER,
	GNOME,
	TRAAL,
	LAST
};

Engine::Engine(const char *mapfile, const char *scorefile)
{
	if (!load_map(mapfile))
		throw "load_map failed: " + std::string(mapfile);
	if (!init_curses())
		throw "init_curses failed";
	if (!init_entities())
		throw "init_entities failed";
	if (!init_score(scorefile))
		throw "init_score failed: " + std::string(scorefile);

	f_running = 1;
}


Engine::~Engine()
{
	for (auto&& e : entities)
		if (e != NULL)
			delete e;
	colors.clear();
	map.clear();
	(void)delwin(gw);
	(void)endwin();
}

bool
Engine::load_map(const char *mapfile)
{
	std::ifstream f;
	std::vector<char> row;
	char c;

	f.exceptions(std::ifstream::badbit);
	f.open(mapfile);
	if (!f.is_open())
		return false;
	while (f.get(c)) {
		if (f.eof())
			break;
		row.push_back(c);
		if (c == '\n') {
			/* XXX: h != hprev */
			h = row.size();
			map.push_back(row);
			row.clear();
		}
	}
	f.close();
	w = map.size();

	return true;
}

/* Initialize curses(3) environment */
bool
Engine::init_curses()
{
	int wr, wc, wy, wx;

	if (!initscr())
		return false;
	noecho();
	cbreak();
	curs_set(false);
	keypad(stdscr, true);
	set_escdelay(0);

	xmax = getmaxx(stdscr);
	ymax = getmaxy(stdscr);

	wr = w;
	wc = h;
	wy = CENTER(ymax, wr);
	wx = CENTER(xmax, wc);
	if ((gw = newwin(wr, wc, wy, wx)) == NULL)
		return false;
	box(gw, 0, 0);
	wxmax = getmaxx(gw);
	wymax = getmaxy(gw);

	colors.push_back(COLOR_BLUE);	/* Wall */
	colors.push_back(COLOR_RED);	/* Path */
	colors.push_back(COLOR_CYAN);	/* Potter */
	colors.push_back(COLOR_GREEN);	/* Gnome */
	colors.push_back(COLOR_YELLOW);	/* Traal */

	start_color();
	use_default_colors();
	for (int i = 1; i < Color::LAST; i++)
		(void)init_pair(i, colors[i-1], -1);

	return true;
}

void
Engine::calc_pos(int *x, int *y)
{
	do {
		*x = rand() % w;
		*y = rand() % h;
		/*
		 * Don't spawn an enemy at the same coordinates with 
		 * another entity.
		 */
		for (const auto& e : entities)
			if (*x == e->get_x() && *y == e->get_y())
				continue;
	} while (map[*x][*y] != ' ');
}

bool
Engine::init_entities()
{
	int i, type, x, y;

	srand(time(nullptr));

	calc_pos(&x, &y);
	/* 
	 * Passing the parameters in reverse order (i.e `y, x` instead of
	 * `x, y`) so that mvwaddch(3) doesn't print the entity on the
	 * wrong coordinates.
	 */
	entities.push_back(new Potter(y, x, Movable::Direction::DOWN, 'P'));
	for (i = 0; i < nenemies; i++) {
		calc_pos(&x, &y);
		/* 
		 * Randomly choose whether we'll create a `Gnome` or
		 * `Traal` enemy.
		 */
		switch (type = rand() % 2) {
		case 0:
			entities.push_back(new Gnome(y, x,
			    Movable::Direction::DOWN, 'G'));
			break;
		case 1:
			entities.push_back(new Traal(y, x,
			    Movable::Direction::DOWN, 'T'));
			break;
		}
	}
	player = (Potter *)entities[0];

	return true;
}

bool
Engine::init_score(const char *scorefile)
{
	return true;
}

void
Engine::kbd_input()
{
	int key, dir;

	switch (key = getch()) {
	case KEY_LEFT:
		dir = Movable::Direction::LEFT;
		break;
	case KEY_RIGHT:
		dir = Movable::Direction::RIGHT;
		break;
	case KEY_UP:
		dir = Movable::Direction::UP;
		break;
	case KEY_DOWN:
		dir = Movable::Direction::DOWN;
		break;
	case 'c':
		menuopts();
		return;
	case ESC: /* FALLTHROUGH */
		/* FIXME: what? */
		f_running = 0;
	default:
		return;
	}

	player->set_newpos(dir, wxmax, wymax);
}

void
Engine::collisions()
{
}

void
Engine::upd_score()
{
}

void
Engine::redraw()
{
	char msg_score[] = "Score: %d";
	char msg_opts[] = "c Controls";
	int color;

	werase(gw);
	erase();
	mvprintw(0, 0, "Potter: (%d, %d)", player->get_x(), player->get_y());
	mvprintw(0, CENTER(xmax, strlen(msg_score)), msg_score, 10);
	mvprintw(0, xmax - strlen(msg_opts), msg_opts);
	mvhline(1, 0, ACS_HLINE, xmax);
	wattron(gw, A_REVERSE);
	for (const auto& row : map) {
		for (const auto& c : row) {
			if (c == '*')
				color = COLOR_PAIR(Color::WALL);
			else if (c == ' ')
				color  = COLOR_PAIR(Color::PATH);
			wattron(gw, color);
			waddch(gw, c);
			wattroff(gw, color);
		}
	}
	for (const auto& e : entities) {
		if (dynamic_cast<Potter *>(e) != nullptr)
			color = COLOR_PAIR(Color::POTTER);
		else if (dynamic_cast<Gnome *>(e) != nullptr)
			color = COLOR_PAIR(Color::GNOME);
		else if (dynamic_cast<Traal *>(e) != nullptr)
			color = COLOR_PAIR(Color::TRAAL);
		wattron(gw, color);
		mvwaddch(gw, e->get_y(), e->get_x(), e->get_sym());
		wattroff(gw, color);
	}
	wattroff(gw, A_REVERSE);
	refresh();
	wrefresh(gw);
}

bool
Engine::is_running()
{
	return f_running;
}

void
Engine::menuopts()
{
	WINDOW *opts;
	int wr, wc, wy, wx;

	wc = 32;
	wr = 9;
	wx = CENTER(xmax, wc);
	wy = CENTER(ymax, wr);
	if ((opts = newwin(wr, wc, wy, wx)) == NULL)
		return;
	werase(opts);
	box(opts, 0, 0);

	mvwprintw(opts, 1, 1, "Up       Move up");
	mvwprintw(opts, 2, 1, "Down     Move down");
	mvwprintw(opts, 3, 1, "Left     Move left");
	mvwprintw(opts, 4, 1, "Right    Move right");
	mvwprintw(opts, 5, 1, "ESC      Quit");
	mvwprintw(opts, 7, 1, "Press any key to quit the menu");

	wrefresh(opts);
	(void)wgetch(opts);
	werase(opts);
	wrefresh(opts);
	(void)delwin(opts);
}
