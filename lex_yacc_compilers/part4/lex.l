%option noyywrap
%{
#include <stdlib.h>
#include "syntax.tab.h"

int	cw = 0;	/* correct words */
int	ww = 0;	/* wrong words */
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
"deffacts"	{ cw++;  return DEFFACTS; }
"defrule"	{ cw++;  return DEFRULE; }
"bind"		{ cw++;  return BIND; }
"read"		{ cw++;  return READ; }
"printout"	{ cw++;  return PRINT; }
"test"		{ cw++;  return TEST; }
"="		{ cw++;  return COMP; }
"("		{ return LPAR; }
")"		{ return RPAR; }
"->"		{ return ARROW; }
{ARITH}		{ cw++;  return ARITH; }
{INT}		{ cw++;  return INT; }
{FLOAT}		{ cw++;  return FLOAT;}
{STR}		{ cw++;  return STR; }
{DEFIN}		{ cw++; return DEFIN; }
{VAR}		{ cw++; return VAR; }
{DELIM}		{ /* ignore whitespace */ }
{COMMENT}	{ /* skip comments */ }
"\n"		{ return NEWLINE; }
.		{ ww++; return UNKNOWN; }
%%
