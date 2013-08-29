/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/18/2013 10:46:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mons.h"
#include "term.h"
#include "main.h"
#include "input.h"
#include "logger.h"
#include "dgn.h"

void firstInit();

int main(int argc, char *argv[]){
	srand(time(NULL));
	atexit(endEnv);
	load_mons();
	firstInit();
	return 0;
}

int initGame(){
	clearScr();
	char *str = readFile("dat/startUpMsg");
	putStringWithAttrib(str,  0, 0);
	free(str);
	displayScr();
	int i = startLoop();
	if(i){
		struct dungeon *dgn = initDgn();
		i = mainLoop(dgn);
		delDgn(dgn);
	}
	return i;
}



void firstInit(){
	initEnv();
	initI();
	int e = 1;
	while(e){
		e = initGame();
	}
}


char* readFile(char *file){

	FILE *fstream = fopen(file, "r");

	int fsize = 0;
	fseek(fstream ,0, SEEK_END);
	fsize  = ftell(fstream);
	fseek(fstream, 0, SEEK_SET);

	char *str =(char*) malloc(fsize);
	fread(str, fsize, 1, fstream);
	fclose(fstream);

	return str;
}

