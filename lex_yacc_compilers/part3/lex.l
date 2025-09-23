%option noyywrap
%{
#include <stdlib.h>
#include "syntax.tab.h"
%}

/*
 * Με βάση το μέρος Α2, υλοποιούμε τις κανονικές εκφράσεις και τις
 * αντιστοιχούμε στα κατάλληλα tokens.
 */
ARITH		"+"|"-"|"*"|"/"|"="
DELIM		[ \t\n]+
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
"deffacts"	{ return DEFFACTS; }
"defrule"	{ return DEFRULE; }
"bind"		{ return BIND; }
"read"		{ return READ; }
"printout"	{ return PRINT; }
"test"		{ return TEST; }
"="		{ return COMP; }
"("		{ return LPAR; }
")"		{ return RPAR; }
"->"		{ return ARROW; }
{ARITH}		{ return ARITH; }
{INT}		{ return INT; }
{FLOAT}		{ return FLOAT;}
{STR}		{ return STR; }
{DEFIN}		{ return DEFIN; }
{VAR}		{ return VAR; }
{DELIM}		{ /* ignore whitespace */ }
{COMMENT}	{ /* skip comments */ }
"\n"		{ return NEWLINE; }
.		{ return UNKNOWN; }
%%
