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
	int sz = darray_usize(dgn->p->loc->itm);
	if(darray_usize(dgn->p->inv) >= 10){
		return;
	}
	if(sz == 1){
		union item *i = getItem(dgn->p->loc, darray_get(dgn->p->loc->itm, 0));
		if(i->type == I_ORB){
			dgn->ohave = 1;
		}else{
			addToInv(dgn->p, i);
		}
	}else if(sz > 1){
		char c = 48;
		int i = 0;
		char *str = malloc(sizeof(char) * 100);
		putStringWithAttrib("Select an item: ", 34, 0);
		for(i = 0; i < sz; i++){
			union item *in = darray_get(dgn->p->loc->itm, i);
			snprintf(str, 100, " -> %c the %s", c, in->w.name);
			putStringWithAttrib(str, 35+i, 0);
			c++;
			i++;
		}
		displayScr();
		char k = 0; // getKch();
		if(k == 0) exit(0);
		if(k < 48 || k > 57) return;
		union item *is = getItem(dgn->p->loc, darray_get(dgn->p->loc->itm, k-48));
		if(is->type == I_ORB){
			dgn->ohave = 1;
		}else{	
			addToInv(dgn->p, is);
	
		}
	}
}

void advHPCnt(struct entity *e){
	e->hpcnt++;
	if(e->hpcnt == 3){
		if(e->hp < e->hpmax) e->hp++;
		e->hpcnt = 0;
	}
}

void turnp(enum direc d, struct dungeon *dgn){
	advHPCnt(dgn->p);
	if(d == GET){
		if(darray_usize(dgn->p->inv) == 25){
			addMsg("You can only have 25 items");
			return;
		}

		if(dgn->p->loc->itm){
			if(darray_usize(dgn->p->loc->itm) > 0){
				gItem(dgn);
			}else{
				return;
			}
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
			if(e->scount == 0){
				advHPCnt(e);
				monsAct(dgn, e);
				e->scount = e->speed;
			}
			i++;
		}
		dgn->p->scount--;
		if(dgn->p->scount == 0) return;
	}

}

int go_up(struct dungeon *dgn){
	if(dgn->p->loc->base != STAIR_UP) return 0;
	if(!dgn->clvl->up){
		if(dgn->ohave){
			return WIN_MV;
		}
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
	if(dgn->ohave){
		strncat(str, "   `fORB of Yendor!`", 500);
	}
	putStringWithAttrib(str, 33, 0);
	free(str);
	int i = 0;
	for(i = 0; i < darray_usize(msg_store); i++){
		putStringWithAttrib(darray_get(msg_store, i), 34+i, 0);
	}
	darray_clear(msg_store);
}

void addMsg(char *msg){
	char *str = strdup(msg);
	darray_add(msg_store, str);
	
}
