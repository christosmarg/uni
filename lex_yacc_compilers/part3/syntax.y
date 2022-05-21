%{
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

extern int	yylex(void);
extern int	yyparse(void);
extern FILE	*yyin, *yyout;
extern char	*yytext;

double	func(char *);
double	calc(char *, double, double);
void	yyerror(const char *);
%}

%union {
	double	dval;
	char	*sval;
}

%token <sval> FUNC STR DEFIN VAR
%token <dval> INT FLOAT
%token NEWLINE UNKNOWN LPAR RPAR ARROW

%type <dval> expr

%start prog

%%
prog:
	{ printf("> "); }
	| prog expr NEWLINE		{ printf("%f\n> ", $2); }
	;

expr:
	INT				{ $$ = $1; }
	| FLOAT				{ $$ = $1; }
	| LPAR FUNC RPAR		{ $$ = func($2); }
	| LPAR FUNC expr expr RPAR	{ $$ = calc($2, $3, $4); }
	| error				{ yyerror("error"); }
	;
%%

double
func(char *op)
{
	double n;
	int rc;

	if (strcmp(op, "quit") == 0) {
		exit(0);
	} else if (strcmp(op, "read") == 0) {
		do {
			printf("read> ");
			rc = scanf("%lf", &n);
			(void)getchar();
		} while (rc != 1);
		return (n);
	}

	yyerror("invalid expression");
	/* NOT REACHED */
	return (0);
}

double
calc(char *op, double arg1, double arg2)
{
	if (strcmp(op, "+") == 0)
		return (arg1 + arg2);
	else if (strcmp(op, "-") == 0)
		return (arg1 - arg2);
	else if (strcmp(op, "*") == 0)
		return (arg1 * arg2);
	else if (strcmp(op, "/") == 0) {
		if (arg2 == 0)
			yyerror("cannot divide by 0");
		return (arg1 / arg2);
	}
	else if (strcmp(op, "e") == 0)
		return (pow(arg1, arg2));
	else if (strcmp(op, "=") == 0)
		return (arg1 == arg2);

	yyerror("invalid expression");
	/* NOT REACHED */
	return (0);
}

void
yyerror(const char *s)
{
	fprintf(stderr, "%s\n", s);
	exit(1);
}

int
main(int argc, char *argv[])
{
	/*if (argc < 2) {*/
		/*fprintf(stderr, "usage: %s input [output]\n", *argv);*/
		/*return (-1);*/
	/*}*/
	/*if ((yyin = fopen(argv[1], "r")) == NULL)*/
		/*err(1, "fopen(%s)", argv[1]);*/
	/*if (argc == 3 && (yyout = fopen(argv[2], "w")) == NULL)*/
		/*err(1, "fopen(%s)", argv[2]);*/

	if (yyparse() == 0)
		fprintf(stderr, "success\n");
	else
		fprintf(stderr, "failure\n");

	return (0);
}
