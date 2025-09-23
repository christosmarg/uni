#ifndef _EXTERN_H_
#define _EXTERN_H_

#define CMD_LEN		32
#define NAME_LEN	32
#define MOVE_TIMEOUT	3
#define ARRLEN(x)	(sizeof(x) / sizeof(x[0]))

enum {
	MOVE_ROCK,
	MOVE_PAPER,
	MOVE_SCISSOR,
};

#endif /* _EXTERN_H_ */
