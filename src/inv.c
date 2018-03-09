/*
 * =====================================================================================
 *
 *       Filename:  inv.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2013 05:23:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "inv.h"
#include "input.h"
#include "logger.h"
#include "term.h"

const char *invHdr = 
"`r       -------INVENTORY--------       `";
const char *invHelp =
"     press Q to quit, press any other letter to select the item";

char *getIName(union item *itm){
	char *s;
	switch(itm->type){
		case I_WEP:
			s = malloc(sizeof(char) * 500);
			snprintf(s, 500, " +%d %s", itm->c.ev, itm->c.name);
			return s;
		case I_CHEST:
			s = malloc(sizeof(char) * 500);
			snprintf(s, 500, " +%d,+%d %s", itm->w.toHit, itm->w.wepp, itm->w.name);
			return s;	
	}
	return NULL;
}

void drawInv(struct dungeon *dgn, int sel){
	clearScr();

	putStringWithAttrib(invHdr, 0, 0);
	char *s = malloc(500 * sizeof(char));
	int i = 0;
	for(i = 0; i < darray_usize(dgn->p->inv) && i < 25; i++){
		union item *itm = darray_get(dgn->p->inv, i);
		char *name = getIName(itm);
		if(i != sel){
			snprintf(s, 500, "     %c --> %s", i+'a', name);
		}else{
			snprintf(s, 500, "     `r%c -->` %s  `r<--`", i+'a', name);
		}
		free(name);
		putStringWithAttrib(s, i+1, 0);
	}
	free(s);
	putStringWithAttrib(invHelp, i+1, 0);
	displayScr();

}


int invp(struct dungeon *dgn){
	while(1){
		drawInv(dgn, -1);
		int c = 'Q'; // getKch();
		
		if(c == NRESTART){
			return NRESTART;
		}else if(c == 'Q'){  //(Q)uit
			break;
		}else{
			int idx = c - 'a';
			log_info("idx = %d", idx);
			if(idx < darray_usize(dgn->p->inv)){
				clearScr();
				drawInv(dgn, idx);
				displayScr();
				/*int k = getKch();*/

			}
		}
	}
	return CONT;
}
