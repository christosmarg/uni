%option noyywrap
%{
#include <stdlib.h>
#include "syntax.tab.h"
%}

/*
 * Με βάση το μέρος Α2, υλοποιούμε τις κανονικές εκφράσεις και τις
 * αντιστοιχούμε στα κατάλληλα tokens.
 */
FUNC		deffacts|defrule|test|bind|read|printout|quit|"+"|"-"|"*"|"/"|"="|"e"
DELIM		[ \t]+
INT		0|[+-]?[1-9]+[0-9]*
FLOAT		[+-]?[0-9]+((\.[0-9]+)([eE][+-]?[0-9]*)?|([eE][+-]?[0-9]*)?)
STR		\"[^\"\\]*(?:\\.[^\"\\]*)*\"
DEFIN		[A-Za-z]+[A-Za-z0-9_-]*
VAR		\?[A-Za-z0-9]+
COMMENT		;.*

/*
 * Όταν βρίσκει οποιοδήποτε token, επιστρέφει την αντίστοιχη κατηγορία στο
 * οποίο ανήκει
 */
%%
{FUNC}		{ yylval.sval = strdup(yytext); return FUNC; }
{INT}		{ yylval.dval = strtod(yytext, NULL); return INT; }
{FLOAT}		{ yylval.dval = strtod(yytext, NULL); return FLOAT; }
{STR}		{ yylval.sval = strdup(yytext); return STR; }
{DEFIN}		{ yylval.sval = strdup(yytext); return DEFIN; }
{VAR}		{ yylval.sval = strdup(yytext); return VAR; }
"("		{ return LPAR; }
")"		{ return RPAR; }
"->"		{ return ARROW; }
\n		{ return NEWLINE; }
{DELIM}		{ /* ignore whitespace */ }
{COMMENT}	{ /* skip comments */ }
.		{ return UNKNOWN; }
%%
