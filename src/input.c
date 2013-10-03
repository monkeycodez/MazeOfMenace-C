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

void initI(){
	noecho();
	raw();
	keypad(stdscr, TRUE);
}

int startLoop(){
	char c = getch();
	if(c == KEY_END || c == CTRL_C_K){
		return 0;
	}
	return c;
}

int getKch(){
	int c = getch();
	if(c == KEY_END || c == CTRL_C_K){
		return NRESTART;
	}
	return c;
}

int do_win(){
	clearScr();
	putStringWithAttrib("You win", 5, 5);
	displayScr();
	int i = getKch();
	if(i) return RESTARTN;
	return NRESTART;
}


int do_ecsDGN(){
	clearScr();
	putStringWithAttrib("You flee from the dungeon\nPress R to restart of Crtl-C to quit", 5, 5);
	displayScr();
	int i = getKch();
	if(i) return RESTARTN;
	return NRESTART;
}

int deathMsg(){
	clearScr();
	char *s = readFile(DEATH_FILE);
	putStringWithAttrib(s, 0, 0);
	displayScr();
	free(s);
	int i = getKch();
	if(i) return RESTARTN;
	return NRESTART;
}


int mainKeyParse(int c, struct dungeon *dgn){
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
			return RESTARTN;
		case '>':
			go_down(dgn);
			break;
		case '<':
			i = go_up(dgn);
			if(i == ESC_DGN){
				return do_ecsDGN();
			}else if(i == WIN_MV){
				return do_win();
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
		case 'i':
			return invp(dgn);
	}
	if(dgn->p->hp <= 0){
		return deathMsg();
	}
	return CONT;
}

int mainLoop(struct dungeon *dgn){
	int c = 0;
	while(1){
		clearScr();
		displayDungeon(dgn);
		displayScr();
		c = getch();
		if(c == KEY_END || c == 3){
			return 0;
		}
		int i = mainKeyParse(c, dgn);
		if(i == CONT) continue;
		if(i == RESTARTN) break;
		if(i == NRESTART) return 0;
	}
	return RESTARTN;
}



