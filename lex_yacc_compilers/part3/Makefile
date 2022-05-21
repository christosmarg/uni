all:
	bison -d syntax.y
	flex lex.l
	cc syntax.tab.c lex.yy.c -lm -o uniclips
	./uniclips input.txt

clean:
	rm -f *.yy.c *.output *.tab.c *.tab.h uniclips *.core
