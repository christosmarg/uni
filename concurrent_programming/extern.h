#ifndef _EXTERN_H_
#define _EXTERN_H_

#define CMD_LEN		32
#define NAME_LEN	32
#define CLIENTS_MAX	64
#define MOVE_TIMEOUT	10
#define BUF_LEN		(BUFSIZ << 2)
#define ARRLEN(x)	(sizeof(x) / sizeof(x[0]))

enum {
	MOVE_ROCK,
	MOVE_PAPER,
	MOVE_SCISSOR,
};

static inline int str2move(const char *);
static inline const char *move2str(int);

static inline int
str2move(const char *str)
{
	if (strcmp(str, "rock") == 0)
		return (MOVE_ROCK);
	else if (strcmp(str, "paper") == 0)
		return (MOVE_PAPER);
	else if (strcmp(str, "scissor") == 0)
		return (MOVE_SCISSOR);
	else
		return (-1);
}

static inline const char *
move2str(int move)
{
	switch (move) {
	case MOVE_ROCK:
		return ("rock");
	case MOVE_PAPER:
		return ("paper");
	case MOVE_SCISSOR:
		return ("scissor");
	default:
		return ("unknown");
	}
}

#endif /* _EXTERN_H_ */
