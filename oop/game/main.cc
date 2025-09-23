#include "Engine.hpp"

/* Program name */
static char *argv0;

static void
die(const std::string& str)
{
	std::cerr << argv0 << ": " << str << "\n";
	exit(1);
}

static void
usage()
{
	std::cerr << "usage: " << argv0 << " <map_file> <score_file>\n";
	exit(1);
}

int
main(int argc, char *argv[])
{
	Engine *eng;
	char *mapfile, *scorefile;
	char name[NAMEMAX];

	argv0 = *argv++;
	if (argc < 3)
		usage();
	mapfile = *argv++;
	scorefile = *argv;

	if (!strcmp(mapfile, scorefile))
		die("input files cannot be the same");
	/* 
	 * We're linking with `lncursesw` so we need to have UTF-8 enabled,
	 * otherwise colors and certain characters might not show up properly
	 * in some terminals.
	 */
	if (!setlocale(LC_ALL, ""))
		die("setlocale");

	do {
		std::cout << "\rPlayer name: ";
		std::cin >> name;
	/* Make sure we read valid input. */
	} while (strlen(name) >= NAMEMAX || std::cin.fail());

	/* 
	 * We'll guarantee the name is null-terminated and has a 
	 * length < NAMEMAX so we don't have to do any checks in 
	 * the other classes.
	 */
	name[strlen(name)] = '\0';

	try {
		eng = new Engine(mapfile, scorefile, name);
	} catch (const std::runtime_error& e) {
		die(e.what());
	}
	while (eng->is_running()) {
		eng->redraw();
		eng->kbd_input();
		eng->enemies_move();
		eng->collisions();
	}
	delete eng;

	return 0;
}
