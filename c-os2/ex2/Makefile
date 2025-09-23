all:
	cc ex3_server.c -lpthread -o ex3_server
	cc ex3_client.c -o ex3_client

run_srv: all
	./ex3_server

run_cli: all
	./ex3_client

clean:
	rm -f ex3_server ex3_client *.core *.o
