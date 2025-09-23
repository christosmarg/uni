#include <sys/socket.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

#include <err.h>
#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "extern.h"

struct command {
	char name[CMD_LEN];
	int (*func)(char *);
};

static int cmd_challenge(char *);
static int cmd_play(char *);
static int cmd_msg(char *);
static int cmd_list(char *);
static int cmd_quit(char *);
static int cmd_help(char *);
static struct command *parse_command(char **);
static void sighandler(int);
static void usage(void);

static struct command commands[] = {
	{ "challenge",	cmd_challenge },	/* /challenge <id> */
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

static int
cmd_challenge(char *args)
{
	char cmd[CMD_LEN];
	int id;

	if (args == NULL) {
		warnx("usage: /challenge <id>");
		return (-1);
	}

	strlcpy(cmd, "challenge", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(challenge, cmd)");
		return (-1);
	}

	id = strtol(args, NULL, 10);
	if (errno == EINVAL || errno == ERANGE) {
		warn("strtol(%s)", args);
		return (-1);
	}
	if (send(fd, &id, sizeof(id), 0) < 0) {
		warn("send(challenge, id)");
		return (-1);
	}

	return (0);
}

static int
cmd_play(char *args)
{
	char cmd[CMD_LEN];
	int move;

	if (args == NULL) {
		warnx("usage: /challenge <rock|paper|scissor>");
		return (-1);
	}

	strlcpy(cmd, "play", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(play, cmd)");
		return (-1);
	}

	if (strcmp(args, "rock") == 0)
		move = MOVE_ROCK;
	else if (strcmp(args, "paper") == 0)
		move = MOVE_PAPER;
	else if (strcmp(args, "scissor") == 0)
		move = MOVE_SCISSOR;
	else
		warnx("invalid move: %s\n", args);

	if (send(fd, &move, sizeof(move), 0) < 0) {
		warn("send(play, move)");
		return (-1);
	}

	return (0);
}

static int
cmd_msg(char *args)
{
	char cmd[CMD_LEN];

	if (args == NULL) {
		warnx("usage: /msg <message>");
		return (-1);
	}

	strlcpy(cmd, "msg", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(msg)");
		return (-1);
	}

	return (0);
}

static int
cmd_list(char *args)
{
	char cmd[CMD_LEN];

	strlcpy(cmd, "list", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(list)");
		return (-1);
	}

	return (0);
}

static int
cmd_quit(char *args)
{
	char cmd[CMD_LEN];

	f_quit = 1;

	strlcpy(cmd, "quit", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(quit)");
		return (-1);
	}

	return (0);
}

static int
cmd_help(char *args)
{
	printf("Available commands:\n");
	printf("/challenge <id|name>\t\tChallenge a player\n");
	printf("/play <rock|paper|scisssor>\tMake a move\n");
	printf("/msg <message>\t\t\tSend a message to the global chat\n");
	printf("/quit\t\t\t\tQuit the game\n");
	printf("/help\t\t\t\tShow this help message\n");

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
	/* FIXME */
	/*if (**args == '\0')*/
		/**args = NULL;*/

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
sighandler(int sig)
{
	f_quit = 1;
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
	struct sigaction sa;
	struct command *cmd;
	char *args, *s;
	char nick[NAME_LEN];
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
	/*
	 * Handle termination signals so we don't exit abnormally (i.e without
	 * cleaning up resources).
	 */
	memset(&sa, 0, sizeof(sa));
	sigfillset(&sa.sa_mask);
	sa.sa_handler = sighandler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		err(1, "sigaction(SIGINT)");
	if (sigaction(SIGTERM, &sa, NULL) < 0)
		err(1, "sigaction(SIGTERM)");

	if (!setlocale(LC_ALL, ""))
		err(1, "setlocale");

	/* Choose nickname. */
	printf("\rEnter nickname (no whitespaces): ");
	fgets(nick, sizeof(nick), stdin);
	s = nick;

	if (*s == '\n' || *s == '\0')
		errx(1, "empty nickname");

	/* Get rid of leading whitespaces. */
	while (*s == ' ')
		s++;

	/* Get rid of trailing newlines and whitespaces. */
	for (; *s != '\0'; s++) {
		if (*s != '\n' && *s != ' ')
			continue;
		*s = '\0';
		break;
	}

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

	/* Send nickname to server */
	if (send(fd, nick, sizeof(nick), 0) < 0)
		err(1, "send(nick)");

	cmd_list(NULL);

	for (;;) {
		if (f_quit)
			break;
		/* TODO redraw */
		if ((cmd = parse_command(&args)) == NULL)
			continue;
		if (cmd->func(args) < 0)
			warnx("/%s(%s) failed\n", cmd->name, args);
		if (args != NULL)
			free(args);
	}
	close(fd);

	return (0);
}
