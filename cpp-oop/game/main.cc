#include <cstring>

#include "Engine.hpp"

/* Program name */
static char *argv0;

static void
die(const std::string& str)
{
	std::cerr << argv0 << ": " << str << std::endl;
	exit(1);
}

static void
usage()
{
	std::cerr << "usage: " << argv0 << " <map_file> <score_file>" << std::endl;
	exit(1);
}

int
main(int argc, char *argv[])
{
	Engine *eng;
	char *mapfile, *scorefile;

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

	try {
		eng = new Engine(mapfile, scorefile);
	} catch (std::string e) {
		die(e);
	}
	while (eng->is_running()) {
		eng->redraw();
		eng->kbd_input();
		eng->enemies_move();
		eng->collisions();
		eng->upd_score();
	}
	delete eng;

	return 0;
}
