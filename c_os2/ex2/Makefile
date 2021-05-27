all:
	cc ex1_1.c -lpthread -o ex1_1
	cc ex1_2.c -lpthread -o ex1_2
	cc ex2.c -lpthread -DLLIM=10 -DULIM=100 -o ex2
	cc ex3_server.c -lpthread -o ex3_server
	cc ex3_client.c -o ex3_client

clean:
	rm -f ex1_1 ex1_2 ex2 ex3_server ex3_client *.core *.o
