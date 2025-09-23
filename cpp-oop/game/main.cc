#include "Engine.hpp"

/* Function declarations */
static void die(const std::string&);

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
	std::cerr << "usage: " << argv0 << " map_file score_file" << std::endl;
	exit(1);
}

int
main(int argc, char *argv[])
{
	Engine eng;
	char *mapfile, *scorefile;

	argv0 = *argv++;

	if (argc < 3)
		usage();
	mapfile = *argv++;
	scorefile = *argv;
	if (!strcmp(mapfile, scorefile))
		die("input files must not be the same");
	if (!setlocale(LC_ALL, ""))
		die("setlocale");

	try {
		eng.init(mapfile, scorefile);
	} catch (std::string e) {
		die(e);
	}

	while (eng.is_running()) {
		eng.kbd_input();
		eng.collisions();
		eng.upd_score();
		eng.redraw();
	}

	return 0;
}
