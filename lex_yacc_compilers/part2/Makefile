all:
	lex -o lex.c lex.l
	cc lex.c -o lex
	./lex input.txt

clean:
	rm -f lex.c lex
