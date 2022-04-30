TARGS = shellcode \
	dash_shellcode \
	stack \
	exploit

#SCRIPTS = 

CC = cc
CFLAGS = -std=c99 -pedantic -Wall -Os -Iinclude -g -z execstack \
	 -fno-stack-protector
LIBS = -Llib

all:
	for targ in ${TARGS} ; do \
		${CC} $${targ}.c ${LIBS} -o $${targ} ; \
		chown root $${targ} ; \
		chmod 4755 $${targ} ; \
	done
	#chmod +x ${SCRIPTS}

clean:
	rm -f ${TARGS} bad *.o *.core
