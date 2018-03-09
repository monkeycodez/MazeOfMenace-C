/*
 * =============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  main file for mmc
 *
 *        Version:  1.0
 *        Created:  12/21/13 10:55:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =============================================================================
 */

//#define LOG_FILE stderr

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>
#include <curses.h>
#include "mons.h"
#include "term.h"
#include "main.h"
#include "input.h"
#include "logger.h"
#include "dgn.h"
#include "alg/mpool.h"
#include "dbg.h"
#include "alg/linkedlist.h"

controls ctrls = { 
	0, 0, 0, 0, 0, 0
};
int is_running = false;
struct dungeon *gdgn = NULL;

void startup_game(){
	gdgn = initDgn();
	ctrls.draw_f = dg_showd;
	ctrls.logic_f = dummy_f;
	ctrls.input_f = dg_input;
	return;	
}

int main(int argc, char *argv[]){
	setlocale(LC_ALL, "");
	srand(time(NULL));

	atexit(endEnv);
	initEnv();
	initI();
	setup_sstr("dat/startUpMsg", startup_game);
	mloop();
	/*_close_log();*/

	return 0;
}

static void (*cb1)(int) = NULL;

void _awk_cb(int i){
	log_add("to free: %x", ctrls.data);
	free(ctrls.data);
	if(cb1 == NULL){set_end();  return;}
	cb1(i);
}

void setup_sstr(char *file, void (*cb)(int)){
	char *str = readFile(file);
	log_add("newstr: %x", str);
	ctrls.data = str;
	ctrls.draw_f = sstr_draw;
	ctrls.logic_f = dummy_f;
	ctrls.input_f = wait_any_key_f;

	after_waitk = _awk_cb;
	cb1 = cb;
}

void set_end(){
	is_running = false;
}

void mloop(){
	is_running = true;
	nodelay(stdscr, TRUE);
	controls ccs;
	while(is_running){
		memcpy(&ccs, &ctrls, sizeof(controls));
		ccs.input_f();
		if(!is_running) break;
		ccs.logic_f();
		if(!is_running) break;
		ccs.draw_f();
		int i = usleep(1000000/30);
		check(i == 0, "usleep failed");
	}
	log_add("Exiting");
}

void sstr_draw(){
	static char *str = NULL;
	if(str == ctrls.data) return;
	str = ctrls.data;
	clearScr();
	putStringWithAttrib(str, 0, 0);
	displayScr();
	return;
}

void wait_any_key_f(){
	int c = getch();
	if(c == ERR) return;
	if(c == KEY_END){
		set_end();
		return;
	}
	if(after_waitk) after_waitk(c);
}

void (*after_waitk)(int i) = NULL;


void dummy_f(){}

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

/*int initGame(){*/
	/*clearScr();*/
	/*char *str = readFile("dat/startUpMsg");*/
	/*putStringWithAttrib(str, 0, 0);*/
	/*free(str);*/
	/*displayScr();*/
	/*int i = startLoop();*/
	/*if(i){*/
		/*struct dungeon *dgn = initDgn();*/
		/*i = mainLoop(dgn);*/
		/*delDgn(dgn);*/
	/*}*/
	/*return i;*/
/*}*/

/*void firstInit(){*/
	/*initEnv();*/
	/*initI();*/
	/*int e = 1;*/
	/*while(e){*/
		/*e = initGame();*/
	/*}*/
/*}*/



