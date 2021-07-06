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

Engine::Engine(const char *mapfile, const char *scorefile, const char *name)
{
	/* 
	 * We'll use std::runtime_error exceptions here because we 
	 * want to display a useful error message since there are
	 * many points of failure.
	 * If we do catch an exception, we'll just "forward" it
	 * to `main`.
	 */
	try {
		/* 
		 * Initialize curses(3) first so we can get the terminal's
		 * dimensions and use them in `load_map`.
		 */
		init_curses();
		load_map(mapfile);
		score = new Score(scorefile, name);
		init_gamewin();
	} catch (const std::ios_base::failure& e) {
		/* 
		 * Kill the curses window, otherwise the terminal output
		 * will be messed up.
		 */
		(void)endwin();
		throw std::runtime_error("error: " + std::string(e.what()));
	} catch (const std::runtime_error& e) {
		(void)endwin();
		throw std::runtime_error("error: " + std::string(e.what()));
	}
	reset_entities();

	init_popup_msgs();
	/* Display a welcome message. */
	popup(p_rules);
	f_running = 1;
}

Engine::~Engine()
{
	delete score;
	free_entities();
	map.clear();
	p_ctrls.clear();
	p_rules.clear();
	p_win.clear();
	p_lose.clear();
	(void)delwin(gw);
	(void)endwin();
}

/*
 * Clean up all moving entities and gems.
 */
void
Engine::free_entities()
{
	player = nullptr;
	for (auto&& e : entities)
		delete e;
	for (auto&& g : gems)
		delete g;
	if (prch != nullptr)
		delete prch;
	entities.clear();
	gems.clear();
}

void
Engine::reset_entities()
{
	free_entities();
	init_entities();
	prch = nullptr;
}

/* 
 * Initialize curses(3) environment 
 */
void
Engine::init_curses()
{
	std::vector<int> colors;

	if (!initscr())
		throw std::runtime_error("init_curses failed");
	/* Don't echo keypresses. */
	noecho();
	/* Disable line buffering. */
	cbreak();
	/* Hide the cursor. */
	curs_set(false);
	/* Allow arrow-key usage. */
	keypad(stdscr, true);
	/* ESC has a small delay after it's pressed, so we'll remove it. */
	set_escdelay(0);
	/* 
	 * Don't wait for a keypress -- just continue if there's no keypress
	 * within 1000 milliseconds. We could set the delay to 0 milliseconds,
	 * but this will most likely burn the CPU.
	 */
	timeout(1000);
	(void)getmaxyx(stdscr, ymax, xmax);

	/* 
	 * This has to follow the same order as the enum declaration at 
	 * the top of the file. Sadly, we cannot use C99's designated 
	 * initialization.
	 */
	colors = {
		COLOR_BLUE,	/* Wall */
		COLOR_RED,	/* Path */
		COLOR_CYAN,	/* Potter */
		COLOR_GREEN,	/* Gnome */
		COLOR_YELLOW,	/* Traal */
		COLOR_WHITE,	/* Stone */
		COLOR_BLACK,	/* Parchment */
	};

	start_color();
	/* Use the terminal's colorscheme. */
	use_default_colors();
	for (int i = 1; i < Color::LAST; i++)
		(void)init_pair(i, colors[i-1], -1);
}

/*
 * Initiliaze the game window. Having a seperate window for the game
 * will make it easier to handle the map and player input.
 */
void
Engine::init_gamewin()
{
	int wr, wc, wy, wx;

	wr = h;
	wc = w;
	wy = CENTER(ymax, wr);
	wx = CENTER(xmax, wc);
	if ((gw = newwin(wr, wc, wy, wx)) == NULL)
		throw std::runtime_error("init_gamewin failed");
	box(gw, 0, 0);
	(void)getmaxyx(gw, wymax, wxmax);
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
	 * every row -- we can now just take a random string and calculate its
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

/*
 * Calculate a new position for an entity or gem.
 */
void
Engine::calc_pos(int *x, int *y)
{
	do {
		*x = rand() % w;
		*y = rand() % h;
		/*
		 * Don't spawn at the same coordinates with another entity 
		 * or gem.
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

	/* Potter is *always* the first entry in `entities`. */
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
int
Engine::popup(const std::vector<std::string>& lines) const
{
	WINDOW *win;
	auto lencmp = [](const std::string& a, const std::string& b) {
		return a.length() < b.length();
	};
	std::size_t vecsz;
	int wr, wc, wy, wx;
	int ch;

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
		return ERR;
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

	/* Save the key we pressed -- it's useful in `round_end`. */
	ch = wgetch(win);
	werase(win);
	wrefresh(win);
	(void)delwin(win);

	return ch;
}

void
Engine::kbd_input()
{
	int key, dir, newx, newy;

	newx = player->get_x();
	newy = player->get_y();
	/* g++ was complaining `dir` wasn't initialized. */
	dir = 0;
	
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
		(void)popup(p_ctrls);
		return;
	case 's':
		(void)popup(score->scores_strfmt());
		break;
	case 'r':
		/* Reset the score as well. */
		upd_score(-score->get_curscore());
		reset_entities();
		break;
	case ESC: /* FALLTHROUGH */
		f_running = 0;
	default:
		/* 
		 * If no key was pressed, just return -- we
		 * don't want to move the player.
		 */
		return;
	}

	if (!collides_with_wall(newx, newy))
		player->set_newpos(dir, wxmax, wymax);
}

/* 
 * Calculate the Eucledean 2D distance from an enemy to the player.
 *
 * Each new distance calculated is added to the `dists` map, which
 * contains the distance and also a direction associated with it.
 */
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

/*
 * Definitely not a sophisticated pathfinding algorithm, but the way it
 * works is this:
 *
 * 1. For each possible direction (west, east, north, south), see if
 *    a movement is possible in the first place -- i.e we won't hit a
 *    wall.
 * 2. Calculate the Eucledean distance for each possible direction
 *    and save it in a map (distance, direction).
 * 3. Sort the map, and get the minimum distance, this is the shortest
 *    path to the player.
 * 4. Get the direction from the minimum pair in the map and go there.
 */
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
		/* Clear previous entity's data. */
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

		/* 
		 * If `dists` is not empty, it means we have found at
		 * least one valid movement.
		 */
		if (!dists.empty()) {
			auto min = std::min_element(dists.begin(),
			    dists.end(), distcmp);
			e->set_newpos(min->second, wxmax, wymax);
		}
	}
}

/*
 * See if the player collides with either an enemy, gem or the parchment. 
 */
void
Engine::collisions()
{
	int px, py, x, y;

	px = player->get_x();
	py = player->get_y();

	/* Collision with an enemy. */
	for (const auto& e : entities) {
		x = e->get_x();
		y = e->get_y();
		if (e != player && px == x && py == y)
			round_end(false);
	}

	/* Collision with a gem. */
	for (auto& g : gems) {
		x = g->get_x();
		y = g->get_y();
		if (px == x && py == y) {
			upd_score(SCORE_STONE);
			delete g;
			/* If we hit a gem, remove it from the vector. */
			gems.erase(std::remove(gems.begin(), gems.end(), g),
			    gems.end());
		}
	}

	/* 
	 * The parchment has been spawned, if we collide with
	 * it, we won the round.
	 */
	if (gems.empty() && prch != nullptr) {
		x = prch->get_x();
		y = prch->get_y();
		if (px == x && py == y) {
			upd_score(SCORE_PARCHMENT);
			delete prch;
			round_end(true);
		}
	/*
	 * If the `gems` vector is empty, we need to spawn the
	 * parchment.
	 */
	} else if (gems.empty() && prch == nullptr)
		spawn_parchment();
}

/*
 * Update the score after each round.
 */
void
Engine::upd_score(int n)
{
	*score << score->get_curname() << score->get_curscore() + n;
}

/*
 * Let the user choose if he wants to start a new round or exit the game.
 */
void
Engine::round_end(bool is_win)
{
	int ch;

	/* 
	 * If we lost, reset the score in case the user starts a new
	 * round. We keep the score only if the player wins the round.
	 */
	if (!is_win)
		upd_score(-score->get_curscore());
	/* If we won, increase the number of enemies. */
	else
		nenemies++;

	/* 
	 * Get out of here only if the user presses 'n' or 'q'
	 * because it's very easy to accidentally mislick and
	 * exit the game.
	 */
	for (;;) {
		switch (ch = popup(is_win ? p_win : p_lose)) {
		case 'n':
			reset_entities();
			return;
		case 'q':
			f_running = 0;
			return;
		}
	}
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

	/* Draw everything. */
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

	/* 
	 * Even though the map is stored as a `std::vector<std::string>`,
	 * we'll loop through it character by character so we can set
	 * the colors.
	 */
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

/* Initialize messages for the popup windows. */
void
Engine::init_popup_msgs()
{
	p_ctrls = {
		"Up       Move up",
		"Down     Move down",
		"Left     Move left",
		"Right    Move right",
		"ESC      Quit",
		"s        High Scores",
		"c        Controls menu",
		"r        Restart game",
		"Press any key to quit the menu",
	};
	p_rules = {
		"                      Babis Potter",
		"--------------------------------------------------------",
		"The objective is to collect all the gems without getting",
		"caught by the Gnomes and Traals!",
		"",
		"You can always see what controls are available by",
		"pressing the 'c' key.",
		"               Press any key to continue",
	};
	p_win = {
		"                  You won!",
		"Press 'n' to play a new round or 'q' to quit.",
	};
	p_lose = {
		"                 You lost!",
		"Press 'n' to play a new round or 'q' to quit.",
	};
}
