#include "Engine.hpp"

enum Color {
	WALL = 1,
	PATH,
	POTTER,
	GNOME,
	TRAAL,
	LAST
};

Engine::Engine()
{
}

Engine::~Engine()
{
	for (auto&& e : entities)
		if (e != NULL)
			delete e;
	(void)endwin();
}

void
Engine::init(const char *mapfile, const char *scorefile)
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
		f_running = 0;
	default:
		return;
	}

	player->set_newpos(dir, xmax, ymax);
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
	char msg_opts[] = "c Controls";
	int color;

	erase();
	/* TODO: add scores and stuff */
	printw("(%d, %d)", player->get_x(), player->get_y());
	mvprintw(0, xmax - strlen(msg_opts), msg_opts);
	mvhline(1, 0, ACS_HLINE, xmax);
	move (2, 0);
	attron(A_REVERSE);
	for (const auto& row : map) {
		for (const auto& c : row) {
			if (c == '*')
				color = COLOR_PAIR(Color::WALL);
			else if (c == ' ')
				color  = COLOR_PAIR(Color::PATH);
			attron(color);
			addch(c);
			attroff(color);
		}
	}
	for (const auto& entity : entities) {
		if (dynamic_cast<Potter *>(entity) != nullptr)
			color = COLOR_PAIR(Color::POTTER);
		else if (dynamic_cast<Gnome *>(entity) != nullptr)
			color = COLOR_PAIR(Color::GNOME);
		else if (dynamic_cast<Traal *>(entity) != nullptr)
			color = COLOR_PAIR(Color::TRAAL);

		attron(color);
		mvaddch(entity->get_y(), entity->get_x(),
		    entity->get_sym());
		attroff(color);
	}
	attroff(A_REVERSE);
	refresh();
}

bool
Engine::is_running()
{
	return f_running;
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
			map.push_back(row);
			row.clear();
		}
	}
	f.close();

	return true;
}

/* Initialize curses(3) environment */
bool
Engine::init_curses()
{
	if (!initscr())
		return false;
	noecho();
	cbreak();
	curs_set(false);
	keypad(stdscr, true);
	set_escdelay(0);

	xmax = getmaxx(stdscr);
	ymax = getmaxy(stdscr);

	colors.push_back(COLOR_BLUE);	/* Wall */
	colors.push_back(COLOR_GREEN);	/* Path */
	colors.push_back(COLOR_MAGENTA);/* Potter */
	colors.push_back(COLOR_CYAN);	/* Gnome */
	colors.push_back(COLOR_YELLOW);	/* Traal */

	start_color();
	use_default_colors();
	for (int i = 1; i < Color::LAST; i++)
		(void)init_pair(i, colors[i-1], -1);

	return true;
}

bool
Engine::init_entities()
{
	srand(time(nullptr));

	entities.push_back(new Potter(15, 10, Movable::Direction::DOWN, 'P'));
	entities.push_back(new Gnome(30, 20, Movable::Direction::DOWN, 'G'));
	entities.push_back(new Traal(50, 26, Movable::Direction::DOWN, 'T'));

	player = (Potter *)entities[0];

	return true;
}

bool
Engine::init_score(const char *scorefile)
{
	return true;
}

void
Engine::menuopts()
{
	WINDOW *opts;
	int w, h, wy, wx;

	w = 32;
	h = 9;
	wy = CENTER(ymax, h);
	wx = CENTER(xmax, w);
	if ((opts = newwin(h, w, wy, wx)) == NULL)
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
