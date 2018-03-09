/*
 * =====================================================================================
 *
 *       Filename:  input.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 01:48:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <ncurses.h>
#include <stdlib.h>
#include "input.h"
#include "dgn.h"
#include "logger.h"
#include "term.h"
#include "turn.h"
#include "main.h"
#include "inv.h"

/*struct key_event *get_event_nc(void *n){*/
	/*key_event *in = malloc(sizeof(key_event));*/
	/*in->code = getch();*/
	/*if(in->code == ERR){*/
		/*free(in);*/
		/*return NULL;*/
	/*}*/
	/*return in;*/
/*}*/

/*int init_in_sys_nc(void **n){*/
	/**n = NULL;*/
	/*timeout(0);*/
	/*raw();*/
	/*noecho();*/
	/*return 1;*/
/*}*/


//Old stuff

void initI(){
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	meta(stdscr, TRUE);
}

/*int startLoop(){*/
	/*char c = getch();*/
	/*if(c == KEY_END || c == CTRL_C_K){*/
		/*return 0;*/
	/*}*/
	/*return c;*/
/*}*/

/*int getKch(){*/
	/*int c = getch();*/
	/*if(c == KEY_END || c == CTRL_C_K){*/
		/*return NRESTART;*/
	/*}*/
	/*return c;*/
/*}*/

/*int do_win(){*/
	/*clearScr();*/
	/*putStringWithAttrib("You win", 5, 5);*/
	/*displayScr();*/
	/*int i = getKch();*/
	/*if(i) return RESTARTN;*/
	/*return NRESTART;*/
/*}*/

void die_scr(){
	/*delDgn(gdgn);*/
	log_info("calling death");
	setup_sstr(DEATH_FILE, NULL);
}


/*int do_ecsDGN(){*/
	/*clearScr();*/
	/*putStringWithAttrib("You flee from the dungeon\n"*/
			/*"Press R to restart of Crtl-C to quit", 5, 5);*/
	/*displayScr();*/
	/*int i = getKch();*/
	/*if(i) return RESTARTN;*/
	/*return NRESTART;*/
/*}*/
int _dirty = true;

/*int deathMsg(){*/
	/*clearScr();*/
	/*char *s = readFile(DEATH_FILE);*/
	/*putStringWithAttrib(s, 0, 0);*/
	/*displayScr();*/
	/*free(s);*/
	/*int i = getKch();*/
	/*if(i) return RESTARTN;*/
	/*return NRESTART;*/
/*}*/


void mainKeyParse(int c, struct dungeon *dgn){
	int i = 0;
	switch(c){
		case KEY_UP:
			turnp(NORTH, dgn);
			break;
		case KEY_DOWN:
			turnp(SOUTH, dgn);
			break;
		case KEY_LEFT:
			turnp(EAST, dgn);
			break;
		case KEY_RIGHT:
			turnp(WEST, dgn);
			break;
		case 'R':
			return;
		case '>':
			go_down(dgn);
			break;
		case '<':
			i = go_up(dgn);
			if(i == ESC_DGN){
				/*return do_ecsDGN();*/
			}else if(i == WIN_MV){
				/*return do_win();*/
			}

			break;
		case 'd':
			turnp(DRINK, dgn);
			break;
		case '.':
			turnp(WAIT, dgn);
			break;
		case 'g':
			turnp(GET, dgn);
			break;
		case 'D':
			dgn->p->hp = 0;
			break;
		default:
			return;
	}
	if(dgn->p->hp <= 0){
		die_scr();
	}
	_dirty = true;
}

/*int mainLoop(struct dungeon *dgn){*/
	/*int c = 0;*/
	/*while(1){*/
		/*clearScr();*/
		/*displayDungeon(dgn);*/
		/*displayScr();*/
		/*c = getch();*/
		/*if(c == KEY_END || c == 3){*/
			/*return 0;*/
		/*}*/
		/*int i = mainKeyParse(c, dgn);*/
		/*if(i == CONT) continue;*/
		/*if(i == RESTARTN) break;*/
		/*if(i == NRESTART) return 0;*/
	/*}*/
	/*return RESTARTN;*/
/*}*/

void in_keysink(){
	int c = getch();
	if(c == ERR) return;
	if(c == KEY_END) set_end();
	return;
}

void dg_input(){
	int c = getch();
	if(c == ERR) return;
	if(c == KEY_END){
		set_end();
		return;
	}
	mainKeyParse(c, gdgn);
}

void dg_showd(){
	if(!_dirty){ return; } 
	if(!gdgn) return;
	clearScr();
	displayDungeon(gdgn);	
	displayScr();
	_dirty = false;
}



