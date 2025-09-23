# See LICENSE file for copyright and license details.
# game

# compiler
CC = c++

# includes and libs
INCS = -Iinclude 
LIBS = -Llib -lncursesw

# flags
CFLAGS = -std=c++14 -pedantic -Wall -Os ${INCS}
LDFLAGS = ${LIBS}

BIN = game

SRC = main.cc \
      Engine.cc \
      Gnome.cc \
      Movable.cc \
      Potter.cc \
      Score.cc \
      Traal.cc \

OBJ = ${SRC:.cc=.o}

all: options ${BIN}

options:
	@echo ${BIN} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

${BIN}: ${OBJ}
	${CC} ${LDFLAGS} ${OBJ} -o $@

.cc.o:
	${CC} -c ${CFLAGS} $<

run:
	./${BIN}

clean:
	rm -f ${BIN} ${OBJ} *.core

.PHONY: all options clean run
