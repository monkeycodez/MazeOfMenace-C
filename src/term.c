/*
 * =====================================================================================
 *
 *       Filename:  term.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/18/2013 05:41:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */


#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "term.h"
#include "logger.h"

#define COL_ORANGE 8
#define COL_ORB 9

struct term{
	char scn[X_DISP_SIZE][Y_DISP_SIZE];
	char col[X_DISP_SIZE][Y_DISP_SIZE];
	int x, y;
	int w, h;
	char colon;
};

struct term *term;

int gameState = 1;
int inited = 0;

int getColorNum(char c);

void initEnv(){
	initscr();
	
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK); 
        init_pair(3, COLOR_GREEN,   COLOR_BLACK);
        init_pair(4,  COLOR_YELLOW,  COLOR_BLACK);
	init_pair(5, COLOR_BLUE,    COLOR_BLACK);
	init_pair(6, COLOR_CYAN,    COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	
	inited = 1;
	
	term = calloc(1, sizeof(struct term));
	term->w = X_DISP_SIZE;
	term->h = Y_DISP_SIZE;
	
	

	curs_set(0);
	
	clearScr();
}

void endEnv(){
	curs_set(1);
	endwin();
}

void putChar(int x, int y, char c, int colNum){
	if(x < term->w && y < term->h){
		term->scn[x][y] = c;
		term->col[x][y] = colNum;
	}
}

static void coladd(char col){
	if(col == term->colon) return;
	attron(A_NORMAL);
	attroff(A_BOLD);
	if(col == CORANGE) {
		attron(COLOR_PAIR(CYELLOW) | A_DIM);
	}else if(col == CGRAY){
		attron(COLOR_PAIR(CWHITE) | A_BOLD);
	}else if(col == CORB){
		attron(COLOR_PAIR(CMAGENTA) | A_BOLD);
	}else{
		attron(COLOR_PAIR(col));
	}
	term->colon = col;
}

void displayScr(){
	int x = 0;
	int y = 0;
	for(x = 0; x < term->w; x++){
		for(y = 0; y < term->h; y++){
			coladd(term->col[x][y]);
			mvaddch(y, x, term->scn[x][y]);
		}
	}
	refresh();
}

void putStringWithAttrib(const char *str, int xStart, int yStart){
	if(inited){
		int size = strlen(str), wait = 0, in = 0, c = 0, currcol = CWHITE;
		int x = yStart, y = xStart;
		for(c = 0; c <= size - 1; c++){
			if(str[c] == '`'&& !in){
				wait = 1;
				in = 1;
			}else if(str[c] =='`' && in){
				currcol = CWHITE;
				attroff(COLOR_PAIR(currcol));
				in = 0;
			}else if(wait){
				currcol = getColorNum(str[c]);
				wait  = 0;
			}else if(str[c] == '\n'){
				y++;
				x = xStart;
			}else{
				term->scn[x][y] = str[c];
				term->col[x][y] = currcol;
				x++;

			}
		}
	}
}

void clearScr(){
	int x = 0;
	int y = 0;
	for(x = 0; x < term->w; x++){
		for(y = 0; y < term->h; y++){
			term->scn[x][y] = ' ';
			term->col[x][y] = CWHITE;
		}
	}
	term->colon = 0;
	erase();
}

int getColorNum(char c){
	switch(c){
		case 'x': return CWHITE;
		case 'r': return CRED;          
		case 'g': return CGREEN;
		case 'o': return CORANGE;
		case 'b': return CBLUE;
		case 'c': return CCYAN;
		case 'p': return CMAGENTA;
		case 'f': return CORB;
		case 'y': return CYELLOW;
		default: return CWHITE;
	}
	
}

