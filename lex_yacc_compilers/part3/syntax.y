%{
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

/* Silence warnings... */
extern int	yylex(void);

/* Input and output files. */
extern FILE	*yyin, *yyout;

extern int	cw;	/* correct words */
extern int	ww;	/* wrong words */
int		ce = 0;	/* correct expressions */
int		we = 0;	/* wrong expressions */

void	yyerror(const char *);
%}

/* Tokens declared from flex. */
%token DEFFACTS DEFRULE BIND READ PRINT TEST ARITH INT FLOAT COMP
%token STR DEFIN VAR LPAR RPAR ARROW NEWLINE UNKNOWN

%start prog

%%
/* Start here. */
prog:
	| prog NEWLINE
	| prog expr
	;

/*
 * Declare numbers. Variables only accept numerical values so add them here as
 * well.
 */
num:
	INT
	| FLOAT
	| VAR
	;

/* Accept any number of strings (for use in printout) */
str:
	STR
	| str STR
	;

/* (= (expr)) */
cmp:
	LPAR COMP expr expr RPAR
	;

/* (test (= (expr))) */
test:
	LPAR TEST cmp RPAR
	;

/* (prinout (str)...) */
print:
	LPAR PRINT str RPAR
	;

fact:
	expr
	| fact expr
	;

/* We match expressions here. */
expr:
	num						/* numbers */
	| cmp				{ ce++; }	/* comparisons */
	| test				{ ce++; }	/* test keyword */
	| print				{ ce++; }	/* (printout "str"...) */
	| LPAR READ RPAR		{ ce++; }	/* (read) */
	| LPAR ARITH expr expr RPAR	{ ce++; }	/* (arithmetic_op (expr)...) */
	| LPAR BIND VAR expr RPAR	{ ce++; }	/* (bind ?var (expr)) */
	| LPAR DEFFACTS DEFIN fact RPAR { ce++; }	/* (deffacts DEF facts...) */
	/* (defrule DEF
	 *	(facts)
	 *	...
	 *	(test)
	 *	->
	 *	(printout))
	 */
	| LPAR DEFRULE DEFIN fact test ARROW print RPAR { ce++; }
	| error				{ we++; if (ce > 0) ce--; }
	;
%%

/* Print errors. */
void
yyerror(const char *s)
{
	fprintf(stderr, "%s\n", s);
}

int
main(int argc, char *argv[])
{
	/* We need at least 1 input and 1 output file... */
	if (argc < 3) {
		fprintf(stderr, "usage: %s input... output\n", *argv);
		return (-1);
	}

	/* Open last file as output. */
	if ((yyout = fopen(argv[--argc], "w")) == NULL)
		err(1, "fopen(%s)", argv[argc]);

	/* Parse all input files in reverse order. */
	while (argc-- > 1) {
		if ((yyin = fopen(argv[argc], "r")) == NULL)
			err(1, "fopen(%s)", argv[argc]);
		/* Parse file */
		if (yyparse() == 0)
			fprintf(yyout, "%s: success\n", argv[argc]);
		else
			fprintf(yyout, "%s: failure\n", argv[argc]);
		fclose(yyin);
	}

	/* Print results. */
	fprintf(yyout, "\n");
	fprintf(yyout, "correct words: %d\n", cw);
	fprintf(yyout, "correct expressions: %d\n", ce);
	fprintf(yyout, "wrong words: %d\n", ww);
	fprintf(yyout, "wrong expressions: %d\n", we);

	fclose(yyout);

	return (0);
}
