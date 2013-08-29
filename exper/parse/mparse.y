

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "e_template.h"

struct e_temp *ce = NULL;

void yyerror(const char *src){
	fprintf(stderr, "error : %s\n", src);
	exit(-1);
}

int yywrap(){
	return 1;
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
	}else{
		yyerror("No PNAME of memb");
	}
}

void printE(){
	printf("Entity %s:\n", ce->name);
	printf("hp: %d-%d\n", ce->hpmin, ce->hpmax);
	printf("def: %d-%d\n", ce->defmin, ce->defmax);
	printf("attk: %d-%d\n", ce->attkmin, ce->attkmax);
}

main(){
	yyparse();
}

%}

%token ENTITY OBRACE EBRACE EQUAL SEMICOLON

%union
{
	char *str;
	int i;
	float f;
}

%token <str> STRING PNAME
%token <i> INT

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
		ce->name = $2;
	}
	ebody 
	{	
		//TODO: add to some list
		printE();
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
	  assign | assign2
	;

assign:
      PNAME EQUAL INT
	{
		assignMembi($1, $3);
	}
	;
assign2:
       PNAME EQUAL STRING 
	{
		assignMembcs($1, $3);
	}
	;
