/*
 * =====================================================================================
 *
 *       Filename:  turn.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/20/2013 12:29:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "turn.h"
#include "dgn.h"
#include "term.h"
#include <stdlib.h>
#include "logger.h"
#include "mons.h"
#include "alg/darray.h"
#include <string.h>
#include "input.h"


void gItem(struct dungeon *dgn){

}


void turnp(enum direc d, struct dungeon *dgn){
	if(d == GET){
		if(dgn->p->loc->itm){
			
		}else{
			return;
		}
	}else if(d == DRINK){
		if(dgn->p->loc->base == FOUNTAIN){
			dgn->p->hp += 10;
			if(dgn->p->hp >= dgn->p->hpmax){
				dgn->p->hp = dgn->p->hpmax;
			}
		}
	}else if(d == WAIT){
		
	}else if(canMove(d, dgn->p)){
		mvEnt(d, dgn->p);
	}else if(canAttk(d, dgn->p)){
		attkEnt(d, dgn->p);
	}else{
		return;
	}
	dgn->p->scount = dgn->p->speed;
	while(1){
		int i = 0;
		while(i < darray_usize(dgn->clvl->mons)){
			struct entity *e = darray_get(dgn->clvl->mons, i);
			e->scount--;
	//		log_info("moving ent #%d, scount : %d\n", i, e->scount);
			if(e->scount == 0){
				monsAct(dgn, e);
				e->scount = e->speed;
			}
			i++;
		}
	//	log_info("usize : %d\n", i);
		dgn->p->scount--;
		if(dgn->p->scount == 0) return;
	}

}

int go_up(struct dungeon *dgn){
	if(dgn->p->loc->base != STAIR_UP) return 0;
	if(!dgn->clvl->up){
		//TODO: test for orb
		return ESC_DGN;
	}
	int dph = dgn->clvl->depth - 1;
	log_info("going up to %d\n", dph);
	struct level *nlvl = dgn->clvl->up;
	dgn->p->loc->ent = NULL;
	dgn->p->loc = nlvl->sdw;
	dgn->p->loc->ent = dgn->p;
	dgn->clvl = nlvl;
	return 0;
}

void go_down(struct dungeon *dgn){
	if(dgn->p->loc->base != STAIR_DOWN) return;
	if(dgn->clvl->down == NULL){
		dgn->clvl->down = createLvl(dgn->clvl->depth+1);
		dgn->clvl->down->up = dgn->clvl;
	}	
	log_info("going down to %d\n", dgn->clvl->depth + 1);
	struct level *nlvl = dgn->clvl->down;
	dgn->p->loc->ent = NULL;
	dgn->p->loc = nlvl->sup;
	dgn->p->loc->ent = dgn->p;
	dgn->clvl = nlvl;
}

struct darray *msg_store = NULL;

void displayBar(struct dungeon *dgn){
	char *str = malloc(sizeof(char) * 500);
	if(!msg_store) msg_store = darray_new();
	char c = 'g';
	if(dgn->p->hp / (float) dgn->p->hpmax < 0.50f){
		c = 'r';
	}
	snprintf(str, 500, "HP: `%c%d/%d`", c,  dgn->p->hp, dgn->p->hpmax );
	putStringWithAttrib(str, 33, 0);
	free(str);
	int i = 0;
	for(i = 0; i < darray_usize(msg_store); i++){
		putStringWithAttrib(darray_get(msg_store, i), 34+i, 0);
	}
	darray_clear(msg_store);
}

void addMsg(char *msg){
	int i = strlen(msg);
	char *str = malloc(sizeof(char) * i);
	strcpy(str, msg);
	darray_add(msg_store, str);
	
}
