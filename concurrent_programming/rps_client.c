#include <err.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
static void cmd_help(char *);
static int init_curses(void);
static struct command *parse_command(char **);
static void usage(void);

static struct command commands[] = {
	{ "challenge",	cmd_challenge },	/* /challenge <name|id> */
	{ "play",	cmd_play },		/* /play <rock|paper|scissor> */
	{ "msg",	cmd_msg },		/* /msg <message> */
	{ "list",	cmd_list },		/* /list */
	{ "quit",	cmd_quit },		/* /quit */
	{ "help",	cmd_help },		/* /help */
};

static int ymax;
static int xmax;
static int f_quit = 0;
static int fd;

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

/* TODO return int... */
static void
cmd_quit(char *args)
{
	f_quit = 1;
	if (send(fd, &f_quit, sizeof(f_quit), 0) < 0)
		;	/* TODO */
}

static void
cmd_help(char *args)
{
	printf("Available commands:\n");
	printf("/challenge <id|name>\t\tChallenge a player\n");
	printf("/play <rock|paper|scisssor>\tMake a move\n");
	printf("/msg <message>\t\t\tSend a message to the global chat\n");
	printf("/quit\t\t\t\tQuit the game\n");
	printf("/help\t\t\t\tShow this help message\n");
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
			if (*args != NULL)
				*args = strdup(*args);
			return (&commands[i]);
		}
	}
	warnx("invalid command: %s", cmd);

	return (NULL);
}

static void
usage(void)
{
	fprintf(stderr, "usage: %1$s [-p port] <hostname|ipv4_addr>\n",
	    getprogname());
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct sockaddr_in sin;
	struct hostent *hp;
	struct command *cmd;
	char *args;
	int port = 9999;
	int ch;

	while ((ch = getopt(argc, argv, "p:")) != -1) {
		switch (ch) {
		case 'p':
			if ((port = atoi(optarg)) < 1024)
				errx(1, "cannot user port number < 1024");
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err(1, "socket(AF_INET)");
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (!inet_aton(*argv, &sin.sin_addr)) {
		if ((hp = gethostbyname(*argv)) == NULL)
			errx(1, "gethostbyname(%s) failed", *argv);
		memcpy(&sin.sin_addr, hp->h_addr, hp->h_length);
	}
	if (connect(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(1, "connect");

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
		if (args != NULL)
			free(args);
	}
	close(fd);

	/*(void)endwin();*/
		
	return (0);
}
