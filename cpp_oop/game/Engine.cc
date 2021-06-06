#include "Engine.hpp"

enum Color {
	WALL = 1,
	PATH,
	POTTER,
	GNOME,
	TRAAL,
	STONE,
	PARCHMENT,
	LAST
};

Engine::Engine(const char *mapfile, const char *scorefile)
{
	if (!init_curses())
		throw std::runtime_error("init_curses failed");
	/* 
	 * We'll use exceptions here because we want to display a useful
	 * error message since `load_map` and `Score`'s constructor
	 * have many points of failure. If we do catch an exception,
	 * we'll just "forward" it to `main`.
	 */
	try {
		load_map(mapfile);
		score = new Score(scorefile);
	} catch (const std::ios_base::failure& e) {
		throw std::runtime_error("error: " + std::string(e.what()));
	} catch (const std::runtime_error& e) {
		throw std::runtime_error("error: " + std::string(e.what()));
	}

	if (!init_gamewin())
		throw std::runtime_error("init_gamewin failed");
	init_entities();
	prch = nullptr;

	/* Initialize messages for the popup windows. */
	ctrls = {
		"Up       Move up",
		"Down     Move down",
		"Left     Move left",
		"Right    Move right",
		"ESC      Quit",
		"s        High Scores",
		"c        Controls menu",
		"Press any key to quit the menu",
	};
	rules = {
		"                      Babis Potter",
		"--------------------------------------------------------",
		"The objective is to collect all the gems without getting",
		"caught by the Gnomes and Traals!",
		"",
		"You can always see what controls are available by",
		"pressing the 'c' key.",
		"               Press any key to continue",
	};

	/* Display a welcome message. */
	popup(rules);
	f_running = 1;
}


Engine::~Engine()
{
	player = nullptr;
	for (auto&& e : entities)
		delete e;
	for (auto&& g : gems)
		delete g;
	if (prch != nullptr)
		delete prch;
	delete score;
	map.clear();
	colors.clear();
	ctrls.clear();
	rules.clear();
	(void)delwin(gw);
	(void)endwin();
}

/* Private methods */

/* 
 * Initialize curses(3) environment 
 */
bool
Engine::init_curses()
{
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
	(void)getmaxyx(stdscr, ymax, xmax);

	colors.push_back(COLOR_BLUE);	/* Wall */
	colors.push_back(COLOR_RED);	/* Path */
	colors.push_back(COLOR_CYAN);	/* Potter */
	colors.push_back(COLOR_GREEN);	/* Gnome */
	colors.push_back(COLOR_YELLOW);	/* Traal */
	colors.push_back(COLOR_WHITE);	/* Stone */
	colors.push_back(COLOR_BLACK);	/* Parchment */

	start_color();
	use_default_colors();
	for (int i = 1; i < Color::LAST; i++)
		(void)init_pair(i, colors[i-1], -1);

	return true;
}

bool
Engine::init_gamewin()
{
	int wr, wc, wy, wx;

	wr = h;
	wc = w;
	wy = CENTER(ymax, wr);
	wx = CENTER(xmax, wc);
	if ((gw = newwin(wr, wc, wy, wx)) == NULL)
		return false;
	box(gw, 0, 0);
	(void)getmaxyx(gw, wymax, wxmax);

	return true;
}

void
Engine::load_map(const char *mapfile)
{
	std::ifstream f;
	std::string str;
	std::size_t l;
	int curline = 1;

	f.exceptions(std::ifstream::badbit);
	f.open(mapfile);
	if (!f.is_open())
		throw std::runtime_error(std::string(mapfile) + 
		    ": cannot open file");
	/* 
	 * Read first row outside the loop so we can get an initial 
	 * row length.
	 */
	if (!std::getline(f, str))
		throw std::runtime_error(std::string(mapfile) +
		    ": cannot read first row");
	map.push_back(str);
	l = str.length();
	while (std::getline(f, str)) {
		/* 
		 * If a row happens to have a different length, the map hasn't
		 * been written properly, so we exit. All rows have to
		 * have the same length.
		 */
		if (l != str.length())
			throw std::runtime_error(std::string(mapfile) +
			    ": rows must have an equal length: line " + 
			    std::to_string(curline));
		
		/* 
		 * The map must not contain anything other than SYM_PATH 
		 * and SYM_WALL.
		 */
		for (char& c : str)
			if (c != SYM_PATH && c != SYM_WALL)
				throw std::runtime_error(std::string(mapfile) + 
				    "the map must contain only spaces and "
				    "asterisks: line: " + 
				    std::to_string(curline));

		map.push_back(str);
		curline++;
	}
	f.close();
	/* 
	 * Since we got here, we know that number of columns is the same for
	 * every row, so we can now just take a random string and calculate its
	 * size in order to get the map's width.
	 */
	w = map[0].length();
	h = map.size();

	/* 
	 * The map has to fit in the screen, obviously. The top 2 lines on 
	 * the Y axis are reserved for the status bar.
	 */
	if (w > xmax || h > ymax - 2)
		throw std::runtime_error(std::string(mapfile) +
		    ": the map doesn't fit to screen");
}

bool
Engine::collides_with_wall(int x, int y) const
{
	if (x < w && y < h)
		return map[y][x] == SYM_WALL;
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
		for (const auto& g : gems)
			if (*x == g->get_x() && *y == g->get_y())
				continue;
	} while (collides_with_wall(*x, *y));
}

void
Engine::init_entities()
{
	int i, x, y, type;

	srand(time(nullptr));
	calc_pos(&x, &y);
	entities.push_back(new Potter(x, y, Movable::Direction::DOWN, SYM_POTTER));
	for (i = 0; i < nenemies; i++) {
		calc_pos(&x, &y);
		/* 
		 * Randomly choose whether we'll create a `Gnome` or
		 * `Traal` enemy.
		 */
		switch (type = rand() % 2) {
		case 0:
			entities.push_back(new Gnome(x, y,
			    Movable::Direction::DOWN, SYM_GNOME));
			break;
		case 1:
			entities.push_back(new Traal(x, y,
			    Movable::Direction::DOWN, SYM_TRAAL));
			break;
		}
	}
	for (i = 0; i < ngems; i++) {
		calc_pos(&x, &y);
		gems.push_back(new Gem(x, y, SYM_STONE));
	}
	player = (Potter *)entities[0];
}

void
Engine::spawn_parchment()
{
	int x, y;

	calc_pos(&x, &y);
	prch = new Gem(x, y, SYM_PARCHMENT);
}

/* 
 * Draw a popup window with the `lines` argument as contents.
 */
void
Engine::popup(const std::vector<std::string>& lines) const
{
	WINDOW *win;
	auto lencmp = [](const std::string& a, const std::string& b) {
		return a.length() < b.length();
	};
	std::size_t vecsz;
	int wr, wc, wy, wx;

	vecsz = lines.size();
	/* 
	 * Find longest string to set the right window width. +2 columns
	 * for the box.
	 */
	wc = std::max_element(lines.begin(), lines.end(), lencmp)->length() + 2;
	/* 
	 * +2 lines for the box, and +1 for the space between the last message
	 * and the rest of the messages.
	 */
	wr = vecsz + 3;
	wx = CENTER(xmax, wc);
	wy = CENTER(ymax, wr);
	if ((win = newwin(wr, wc, wy, wx)) == NULL)
		return;
	werase(win);
	box(win, 0, 0);
	for (std::size_t i = 0; i < vecsz; i++) {
		if (i != vecsz - 1)
			mvwprintw(win, i + 1, 1, lines[i].c_str());
		/*
		 * The last message is always the "quit menu" message, so
		 * we'll leave an empty line before we print it.
		 */
		else
			mvwprintw(win, i + 2, 1, lines[i].c_str());
	}
	wrefresh(win);
	(void)wgetch(win);
	werase(win);
	wrefresh(win);
	(void)delwin(win);
}

void
Engine::calc_dist(std::map<int, int>& dists, int ex, int ey, int dir) const
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

	dir = 0;
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
		popup(ctrls);
		return;
	case 's':
		popup(score->scores_strfmt());
		break;
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
	auto distcmp = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
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
			    dists.end(), distcmp);
			e->set_newpos(min->second, wxmax, wymax);
		}
	}
}

/* TODO: define constants for scores */
void
Engine::collisions()
{
	int px, py, x, y;

	px = player->get_x();
	py = player->get_y();

	for (const auto& e : entities) {
		x = e->get_x();
		y = e->get_y();
		if (e != player && px == x && py == y) {
			/* TODO: Handle this. */
		}
	}
	for (auto& g : gems) {
		x = g->get_x();
		y = g->get_y();
		if (px == x && py == y) {
			upd_score(10);
			delete g;
			gems.erase(std::remove(gems.begin(), gems.end(), g),
			    gems.end());
		}
	}
	if (gems.empty() && prch != nullptr) {
		x = prch->get_x();
		y = prch->get_y();
		if (px == x && py == y) {
			upd_score(100);
			/* TODO: YOU WON + delete + reset */
		}
	} else if (gems.empty() && prch == nullptr)
		spawn_parchment();
}

void
Engine::upd_score(int n)
{
	*score << score->get_curname() << score->get_curscore() + n;
}

void
Engine::redraw() const
{
	const char msg_pos[] = "Potter: (%d, %d)";
	const char msg_score[] = "Score: %d (%s)";
	const char msg_opts[] = "c Controls";

	werase(gw);
	erase();
	
	/* Draw top bar info. */
	mvprintw(0, 0, msg_pos, player->get_x(), player->get_y());
	mvprintw(0, CENTER(xmax, strlen(msg_score)), msg_score,
	    score->get_curscore(), score->get_curname());
	mvprintw(0, xmax - strlen(msg_opts), msg_opts);
	mvhline(1, 0, ACS_HLINE, xmax);

	/* Draw everything */
	wattron(gw, A_REVERSE);
	draw_map();
	draw_entities();
	draw_gems();
	if (prch != nullptr)
		draw_parchment();
	wattroff(gw, A_REVERSE);
	refresh();
	wrefresh(gw);
}

void
Engine::draw_map() const
{
	int color;

	for (const auto& row : map) {
		for (const auto& c : row) {
			if (c == SYM_WALL)
				color = COLOR_PAIR(Color::WALL);
			else if (c == SYM_PATH)
				color = COLOR_PAIR(Color::PATH);
			wattron(gw, color);
			waddch(gw, c);
			wattroff(gw, color);
		}
	}
}

void
Engine::draw_entities() const
{
	int color;

	for (const auto& e : entities) {
		/* Determine subclass type and assign colors accordingly. */
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
}

void
Engine::draw_gems() const
{
	int color;

	for (const auto& g : gems) {
		if (g->get_sym() == SYM_STONE)
			color = COLOR_PAIR(Color::STONE);
		else if (g->get_sym() == SYM_PARCHMENT)
			color = COLOR_PAIR(Color::PARCHMENT);
		wattron(gw, color);
		mvwaddch(gw, g->get_y(), g->get_x(), g->get_sym());
		wattroff(gw, color);
	}
}

void
Engine::draw_parchment() const
{
	wattron(gw, COLOR_PAIR(Color::PARCHMENT));
	mvwaddch(gw, prch->get_y(), prch->get_x(), prch->get_sym());
	wattroff(gw, COLOR_PAIR(Color::PARCHMENT));
}

bool
Engine::is_running() const
{
	return f_running;
}
