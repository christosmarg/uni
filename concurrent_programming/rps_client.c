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

#define NTDS	2

struct command {
	char name[CMD_LEN];
	int (*func)(char *);
};

static int cmd_challenge(char *);
static int cmd_accept(char *);
static int cmd_msg(char *);
static int cmd_list(char *);
static int cmd_quit(char *);
static int cmd_help(char *);
static struct command *parse_command(char **);
static void sighandler(int);
static void usage(void);

static struct command commands[] = {
	{ "challenge",	cmd_challenge },/* /challenge <id> <rock|paper|scissor> */
	{ "accept",	cmd_accept },	/* /accept <rock|paper|scissor> */
	{ "msg",	cmd_msg },	/* /msg <message> */
	{ "list",	cmd_list },	/* /list */
	{ "quit",	cmd_quit },	/* /quit */
	{ "help",	cmd_help },	/* /help */
};

static int ymax;
static int xmax;
static int fd;
static volatile sig_atomic_t f_quit = 0;

static int
cmd_challenge(char *args)
{
	char cmd[CMD_LEN], *s;
	int id, move;

	if (args == NULL) {
		warnx("usage: /challenge <id> <rock|paper|scissor>");
		return (-1);
	}
	s = strchr(args, ' ');
	if (s == NULL || *s == '\0') {
		warnx("usage: /challenge <id> <rock|paper|scissor>");
		return (-1);
	}
	while (*s == ' ')
		s++;
	if (*s == '\0') {
		warnx("usage: /challenge <id> <rock|paper|scissor>");
		return (-1);
	}
	if ((move = str2move(s)) < 0) {
		warnx("invalid move: %s", s);
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

	if (send(fd, &move, sizeof(move), 0) < 0) {
		warn("send(challenge, move)");
		return (-1);
	}

	return (0);
}

static int
cmd_accept(char *args)
{
	char cmd[CMD_LEN];
	int move;

	if (args == NULL) {
		warnx("usage: /challenge <rock|paper|scissor>");
		return (-1);
	}

	strlcpy(cmd, "accept", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(accept, cmd)");
		return (-1);
	}

	if ((move = str2move(args)) < 0) {
		warnx("invalid move: %s", args);
		return (-1);
	}

	if (send(fd, &move, sizeof(move), 0) < 0) {
		warn("send(accept, move)");
		return (-1);
	}

	return (0);
}

static int
cmd_msg(char *args)
{
	char cmd[CMD_LEN];
	size_t len;

	if (args == NULL) {
		warnx("usage: /msg <message>");
		return (-1);
	}

	strlcpy(cmd, "msg", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(msg)");
		return (-1);
	}

	len = strlen(args) + 1;
	if (send(fd, &len, sizeof(len), 0) < 0) {
		warn("send(msg, len)");
		return (-1);
	}

	if (send(fd, args, len, 0) < 0) {
		warn("send(msg, msg)");
		return (-1);
	}

	return (0);
}

static int
cmd_list(char *args)
{
	char cmd[CMD_LEN], buf[BUF_LEN];

	strlcpy(cmd, "list", sizeof(cmd));
	if (send(fd, cmd, sizeof(cmd), 0) < 0) {
		warn("send(list)");
		return (-1);
	}

	if (recv(fd, buf, sizeof(buf), 0) < 0) {
		warn("recv(list)");
		return (-1);
	}
	puts(buf);

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
	printf("/challenge <id|name> <rock|paper|scissor>\t\t"
	    "Challenge a player\n");
	printf("/accept <rock|paper|scisssor>\tAccept challenge\n");
	printf("/msg <message>\t\t\tSend a message to the global chat\n");
	printf("/quit\t\t\t\tQuit the game\n");
	printf("/help\t\t\t\tShow this help message\n");

	return (0);
}

static struct command *
parse_command(char **args)
{
	char buf[BUF_LEN], *line, *cmd, *s;
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
	char *args;
	char *s;
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

	/* Set up connection. */
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

	/* Print list of available players. */
	cmd_list(NULL);

	/* Main game loop. */
	for (;;) {
		if (f_quit)
			break;
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
