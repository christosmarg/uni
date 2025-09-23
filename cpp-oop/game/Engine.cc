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
	player = nullptr;
	for (auto&& e : entities)
		delete e;
	delete score;
	map.clear();
	colors.clear();
	(void)delwin(gw);
	(void)endwin();
}

/* Private methods */

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
			w = row.size();
			map.push_back(row);
			row.clear();
		}
	}
	f.close();
	h = map.size();

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
	/* Allow arrow key presses. */
	keypad(stdscr, true);
	/* ESC has a small delay after it's pressed, so remove it. */
	set_escdelay(0);
	/* Don't wait for a keypress, just continue if there's nothing. */
	timeout(1000);

	xmax = getmaxx(stdscr);
	ymax = getmaxy(stdscr);

	wr = h;
	wc = w;
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

bool
Engine::collides_with_wall(int x, int y)
{
	if (x < w && y < h)
		return map[y][x] == '*';
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
	} while (collides_with_wall(*x, *y));
}

bool
Engine::init_entities()
{
	int i, x, y, type;

	srand(time(nullptr));

	calc_pos(&x, &y);
	/* 
	 * Passing the parameters in reverse order (i.e `y, x` instead of
	 * `x, y`) so that mvwaddch(3) doesn't print the entity on the
	 * wrong coordinates.
	 */
	entities.push_back(new Potter(x, y, Movable::Direction::DOWN, 'P'));
	for (i = 0; i < nenemies; i++) {
		calc_pos(&x, &y);
		/* 
		 * Randomly choose whether we'll create a `Gnome` or
		 * `Traal` enemy.
		 */
		switch (type = rand() % 2) {
		case 0:
			entities.push_back(new Gnome(x, y,
			    Movable::Direction::DOWN, 'G'));
			break;
		case 1:
			entities.push_back(new Traal(x, y,
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
	score = new Score(scorefile);

	return true;
}

void
Engine::ctrl_menu()
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

void
Engine::calc_dist(std::map<int, int>& dists, int ex, int ey, int dir)
{
	int px, py, dx, dy, d;

	px = player->get_x();
	py = player->get_y();
	dx = ex - px;
	dy = ey - py;
	d = floor(sqrt(dx * dx + dy * dy));
	dists.insert(std::pair<int, int>(d, dir));
}

/* Public methods */

void
Engine::kbd_input()
{
	int key, dir, newx, newy;

	newx = player->get_x();
	newy = player->get_y();
	
	switch (key = getch()) {
	case KEY_LEFT:
		newx--;
		dir = Movable::Direction::LEFT;
		break;
	case KEY_RIGHT:
		newx++;
		dir = Movable::Direction::RIGHT;
		break;
	case KEY_UP:
		newy--;
		dir = Movable::Direction::UP;
		break;
	case KEY_DOWN:
		newy++;
		dir = Movable::Direction::DOWN;
		break;
	case 'c':
		ctrl_menu();
		return;
	case ESC: /* FALLTHROUGH */
		/* FIXME: what? */
		f_running = 0;
	default:
		return;
	}

	if (!collides_with_wall(newx, newy))
		player->set_newpos(dir, wxmax, wymax);
}

/* FIXME: move asynchronously */
void
Engine::enemies_move()
{
	std::map<int, int> dists;
	int ex, ey;
	auto mindist = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
		return a.first < b.second;
	};

	for (const auto& e : entities) {
		if (e == player)
			continue;
		ex = e->get_x();
		ey = e->get_y();
		dists.clear();
		/* West */
		if (!collides_with_wall(ex - 1, ey))
			calc_dist(dists, ex - 1, ey, Movable::Direction::LEFT);
		/* East */
		if (!collides_with_wall(ex + 1, ey))
			calc_dist(dists, ex + 1, ey, Movable::Direction::RIGHT);
		/* North */
		if (!collides_with_wall(ex, ey - 1))
			calc_dist(dists, ex, ey - 1, Movable::Direction::UP);
		/* South */
		if (!collides_with_wall(ex, ey + 1))
			calc_dist(dists, ex, ey + 1, Movable::Direction::DOWN);

		if (!dists.empty()) {
			auto min = std::min_element(dists.begin(),
			    dists.end(), mindist);
			e->set_newpos(min->second, wxmax, wymax);
		}
	}
}

void
Engine::collisions()
{
	int px, py, ex, ey;

	px = player->get_x();
	py = player->get_y();

	for (const auto& e : entities) {
		ex = e->get_x();
		ey = e->get_y();
		if (e != player && px == ex && py == ey) {
			/* TODO: increase score */
		}
	}
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

	/* TODO: print more info */
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
