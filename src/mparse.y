

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "e_template.h"
#include "mons.h"
#include "y.tab.h"
#include "term.h"

struct e_temp *ce = NULL;
extern int line_num;
extern FILE* yyin;
int yylex();
int yyparse();

void yyerror(const char *src){
	fprintf(stderr, "error : %s, line: %d \n", src, line_num);
	exit(-1);
}

int yywrap(){
	return 1;
}

void stripString(char *s){
	printf("%s\n", s);
	int i = 0;
	while(*(s + i + 1) != '"'){
		*(s + i) = *(s + i + 1);
		i++;
	}
	*(s + i) = 0;
	printf("%s\n", s);
}

void assignMembcs(char *memb, void *data){

}

void assignMembi(char *memb, int data){
	if(ce == NULL) return;
	if(strstr(memb, HPMAX_S)){
		ce->hpmax = data;
	}else if(strstr(memb, HPMIN_S)){
		ce->hpmin = data;
	}else if(strstr(memb, ATTKMIN_S)){
		ce->attkmin = data;
	}else if(strstr(memb, ATTKMAX_S)){
		ce->attkmax = data;
	}else if(strstr(memb, DEFMIN_S)){
		ce->defmin = data;
	}else if(strstr(memb, DEFMAX_S)){
		ce->defmax = data;
	}else if(strstr(memb, DEPTH_S)){
		ce->depth = data;
	}else{
		yyerror("No PNAME of memb");
	}
}

void assignMembc(char *memb, char data){
	if(strstr(memb, DISP_S)){
		ce->disp = data;
	}
}

int getPValCol(char *data){
	if(strstr(data, CWHITE_S)){
		return CWHITE;
	}	
	if(strstr(data, CRED_S)){
		return CRED;
	}	
	if(strstr(data, CGREEN_S)){
		return CGREEN;
	}	
	if(strstr(data, CBLUE_S)){
		return CBLUE;
	}
	if(strstr(data, CYELLOW_S)){
		return CYELLOW;
	}
	if(strstr(data, CCYAN_S)){
		return CCYAN;
	}
	if(strstr(data, CMAGENTA_S)){
		return CMAGENTA;
	}
	if(strstr(data, CORANGE_S)){
		return CORANGE;
	}
	if(strstr(data, CORB_S)){
		return CORB;
	}
	if(strstr(data, CGRAY_S)){
		return CGRAY;
	}
	return CWHITE;
}

void assignMembv(char *memb, char *data){
	if(strstr(memb, COL_S)){
		ce->color = getPValCol(data);		
	}
}

void printE(){
	printf("Entity %s:\n", ce->name);
	printf("hp: %d-%d\n", ce->hpmin, ce->hpmax);
	printf("def: %d-%d\n", ce->defmin, ce->defmax);
	printf("attk: %d-%d\n", ce->attkmin, ce->attkmax);
}

void parseEnts(){
	FILE *f = fopen("dat/monsdef", "r");
	if(!f) yyerror("Cannot open file");
	
	yyin = f;
	yyparse();
}

%}

%token ENTITY OBRACE EBRACE EQUAL SEMICOLON

%union
{
	char *str;
	int i;
	float f;
	char c;
}

%token <str> STRING PNAME PVAL
%token <i> INT
%token <c> CHAR

%%

commands:
	| commands command SEMICOLON
	;

command:
	entity 
	;

entity:
      	ENTITY STRING
	{
		if(ce){
			 yyerror("cannot have entity inside entity");
		}
		ce = malloc(sizeof(struct e_temp));
		stripString($2);
		ce->name = $2;
	}
	ebody 
	{	
		//TODO: add to some list
		printE();
		add_mons(ce);
		ce = NULL;
	}
	;

ebody:
     	OBRACE estaments EBRACE
	;

estaments:
	 | 
	estaments estatement SEMICOLON
	;

estatement:
	  assign_c | assign_s | assign_i | assign_v 
	;

assign_i:
      PNAME EQUAL INT
	{
		assignMembi($1, $3);
	}
	;
assign_s:
       PNAME EQUAL STRING 
	{
		stripString($3);
		assignMembcs($1, $3);
	}
	;
assign_c:
	PNAME EQUAL CHAR
	{
		assignMembc($1, $3);
	}
	;
assign_v:
	PNAME EQUAL PVAL
	{
		assignMembv($1, $3);
	}
	;
