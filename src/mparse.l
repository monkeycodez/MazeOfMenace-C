
%{

#include "y.tab.h"
#include <stdio.h>

unsigned int line_num = 1;

%}

%%

entity			{ return ENTITY; }
\{			{ return OBRACE; }
\}			{ return EBRACE; }
=			{ return EQUAL; }
$[A-Z]+			{ yylval.str = strdup(yytext); return PVAL; }
[a-zA-z]+ 		{ yylval.str = strdup(yytext); return PNAME; }
\'.\'			{ yylval.c = yytext[1]; return CHAR;}
\"[^\"]+\"		{ yylval.str = strdup(yytext); return STRING; }
[0-9]+			{ yylval.i = atoi(yytext);   return INT; } 
[ \t]+			;
#[^\n]*\n		;
;			{ return SEMICOLON; }
\n			{ line_num++; }
