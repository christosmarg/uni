CC = cc

all:
	make -f Makefile.rpc
	${CC} sock_client.c -o sock_client

clean:
	make -f Makefile.rpc clean
	rm -f sock_client *.core
