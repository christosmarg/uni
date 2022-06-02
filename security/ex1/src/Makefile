TARGS = priv \
	encrypt \
	decrypt \
	sign \
	verify

SCRIPTS = atoh \
	  htoa

CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Os -Iinclude
LIBS = -Llib -lcrypto

all:
	for targ in ${TARGS} ; do \
		${CC} $${targ}.c ${LIBS} -o $${targ} ; \
	done
	chmod +x ${SCRIPTS}

clean:
	rm -f ${TARGS} *.o *.core
