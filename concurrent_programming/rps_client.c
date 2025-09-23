#include <err.h>
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRLEN(x)	(sizeof(x) / sizeof(x[0]))

struct command {
	char name[32];
	void (*func)(char *);
};

static void cmd_challenge(char *);
static void cmd_play(char *);
static void cmd_msg(char *);
static void cmd_list(char *);
static void cmd_quit(char *);
static int init_curses(void);
static struct command *parse_command(char **);

static struct command commands[] = {
	{ "challenge",	cmd_challenge },	/* /challenge <name|id> */
	{ "play",	cmd_play },		/* /play <rock|paper|scissor> */
	{ "msg",	cmd_msg },		/* /msg <message> */
	{ "list",	cmd_list },		/* /list */
	{ "quit",	cmd_quit },		/* /quit */
};

static int ymax;
static int xmax;
static volatile bool f_quit = false;

static void
cmd_challenge(char *args)
{
}

static void
cmd_play(char *args)
{
	/* TODO add fuzzy parsing */
	/* TODO ask for command and send it to server */
}

static void
cmd_msg(char *args)
{
}

static void
cmd_list(char *args)
{
}

static void
cmd_quit(char *args)
{
	f_quit = true;
}

static int
init_curses(void)
{
	if (!initscr())
		return (-1);

	/* Don't echo keypresses. */
	noecho();
	/* Disable line buffering. */
	cbreak();
	/* Hide the cursor. */
	curs_set(false);
	/* Allow arrow-key usage. */
	keypad(stdscr, true);
	/* ESC has a small delay after it's pressed. Remove it. */
	set_escdelay(0);
	/* 
	 * Don't wait for a keypress -- just continue if there's no keypress
	 * within 1000 milliseconds. We could set the delay to 0 milliseconds,
	 * but this will most likely burn the CPU.
	 */
	timeout(1000);
	(void)getmaxyx(stdscr, ymax, xmax);
	start_color();
	/* Use the terminal's colorscheme. */
	use_default_colors();
	/* TODO init pairs */

	return (0);
}

static struct command *
parse_command(char **args)
{
	char buf[BUFSIZ], *line, *cmd, *s;
	int i;

	printf("\r> ");
	fgets(buf, sizeof(buf), stdin);
	line = buf;

	if (*line == '\n' || *line == '\0') {
		warnx("empty command");
		return (NULL);
	}

	/* Get rid of leading whitespaces. */
	while (*line == ' ')
		line++;

	/* Get rid of trailing newlines. */
	for (s = line; *s != '\0'; s++) {
		if (*s != '\n')
			continue;
		*s = '\0';
		break;
	}

	/* Commands must start with /. */
	if (*line != '/') {
		warnx("please enter a command");
		return (NULL);
	}
	line++;

	*args = strchr(line, ' ');
	if (*args != NULL) {
		while (**args == ' ')
			(*args)++;
	}

	cmd = strtok(line, " ");
	if (cmd == NULL) {
		warn("strtok() failed");
		return (NULL);
	}

	/* Match command. */
	for (i = 0; i < ARRLEN(commands); i++) {
		if (strncmp(cmd, commands[i].name,
		    strlen(commands[i].name)) == 0) {
			*args = strdup(*args);
			return (&commands[i]);
		}
	}
	warnx("invalid command: %s", cmd);

	return (NULL);
}

int
main(int argc, char *argv[])
{
	struct command *cmd;
	char *args;

	/* TODO command line network options */
	/* TODO signals */
	/* TODO nickname selection (server keeps asking until unique) */

	if (!setlocale(LC_ALL, ""))
		err(1, "setlocale");

	/*if (init_curses() < 0)*/
		/*errx(1, "could not initialize ncurses");*/

	for (;;) {
		if (f_quit)
			break;
		/* TODO redraw */
		if ((cmd = parse_command(&args)) == NULL)
			continue;
		/* TODO connect to server */
		cmd->func(args);
		free(args);
	}

	/*(void)endwin();*/
		
	return (0);
}
