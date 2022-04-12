TARGS = priv

CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Os -Iinclude
LIBS = -Llib -lcrypto

all:
	for targ in ${TARGS} ; do \
		${CC} $${targ}.c ${LIBS} -o $${targ} ; \
	done

clean:
	rm -f ${TARGS} *.o *.core
