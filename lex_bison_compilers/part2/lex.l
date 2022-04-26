%option noyywrap

%{
#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"

int lineno = 1;
%}

DELIM		[ \t]+
INT		0|[+-]?[1-9]+[0-9]*
FLOAT		[+-]?[0-9]+((\.[0-9]+)([eE][+-]?[0-9]*)?|([eE][+-]?[0-9]*)?)
STR		\"[^\"\\]*(?:\\.[^\"\\]*)*\"
DEFIN		[A-Za-z]+[A-Za-z0-9_-]*
VAR		\?[A-Za-z0-9]+
COMMENT		;.*
KEYWORD		deffacts|defrule|test|bind|read|printout
OPERATOR	=|\+|-|\*|\/
UNKNOWN		[^ {DELIM}\n]+
%%

{DELIM}		{ /* ignore whitespace */ }
{INT}		{ return TOK_INT; }
{FLOAT}		{ return TOK_FLOAT; }
{STR}		{ return TOK_STR; }
{DEFIN}		{ return TOK_DEFIN; }
{VAR}		{ return TOK_VAR; }
{COMMENT}	{ /* skip comments */ }
{KEYWORD}	{ return TOK_KEYWORD; }
{OPERATOR}	{ return TOK_OPERATOR; }
{UNKNOWN}	{ return TOK_UNKNOWN; }
\n		{ lineno++; }
<<EOF>>		{ printf("EOF\n"); exit(0); }
%%

static char *tokens[] = {
	"INT",		/* integers */
	"FLOAT",	/* floats */
	"STR",		/* strings */
	"DEFIN",	/* definitions */
	"VAR",		/* variables */
	"KEYWORD",	/* keywords */
	"OPERATOR",	/* operators */
	"UNKNOWN",	/* unknown token */
};

int
main(int argc, char *argv[])
{
	int tok;

	if (argc < 2) {
		fprintf(stderr, "usage: %s input [output]\n", *argv);
		return (-1);
	}
	if ((yyin = fopen(argv[1], "r")) == NULL)
		err(1, "fopen(%s)", argv[1]);
	if (argc == 3 && (yyout = fopen(argv[2], "w")) == NULL)
		err(1, "fopen(%s)", argv[2]);

	while ((tok = yylex()) >= 0) {
		fprintf(yyout, "line: %d\ttoken=%s\tval='%s'\n",
		    lineno, tokens[tok-1], yytext);
	}

	return (0);
}
