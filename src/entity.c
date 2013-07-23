/*
 * =====================================================================================
 *
 *       Filename:  entity.c
 *
 *    Description:  Entity stuff
 *
 *        Version:  1.0
 *        Created:  07/20/2013 12:21:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <string.h>
#include "alg/darray.h"
#include "dgn.h"
#include <stdlib.h>
#include "turn.h"

void equipItm(struct entity *e, union item *i){
	if(i->type == I_WEP){
		if(e->wep != NULL){
			addToInv(e, e->wep);
		}
		e->wep = i;
	}else if(i->type == I_CHEST){
		if(e->chest != NULL){
			addToInv(e, e->chest);
		}
		e->chest = i;
	}
}

void addToInv(struct entity *e, union item *i){
	if(!e->inv){
		e->inv = darray_new();
	}
	darray_add(e->inv, i);
}

union item *rmFromInv(struct entity *e, union item *i){
	if(e->inv == NULL) return NULL;
	union item *in = darray_remove(e->inv, darray_search(e->inv, i));
	return in;
}

union item *getItem(struct tile *t, union item *i){
	if(t->itm == NULL) return NULL;
	union item *in = darray_remove(t->itm, darray_search(t->itm, i));
	if(darray_usize(t->itm) == 0){
		darray_del(t->itm);
	}
	return in;
}

void chkDeath(struct entity *ent){
	if(ent->hp <= 0){
		ent->loc->ent = NULL;
		ent->loc = NULL;
		ent->dead = 1;
		if(ent->list)
			darray_remove(ent->list, darray_search(ent->list, ent));
	}
}

int canMove(enum direc d, struct entity *ent){
	struct tile *n = NULL;
	switch (d){
		case NORTH: 
			n = ent->loc->n;
			break;
		case SOUTH:
			n = ent->loc->s;
			break;
		case WEST:
			n = ent->loc->w;
			break;
		case EAST:
			n = ent->loc->e;
			break;
		default:
			return 0;
	}
	if(!n) return 0 ;
	if(!n->ent) return 1;
	return 0;
}

int canAttk(enum direc d, struct entity *ent){
	struct tile *n = NULL;
	switch (d){
		case NORTH: 
			n = ent->loc->n;
			break;
		case SOUTH:
			n = ent->loc->s;
			break;
		case WEST:
			n = ent->loc->w;
			break;
		case EAST:
			n = ent->loc->e;
			break;
		default:
			return 0;
	}
	if(!n) return 0;
	if(!n->ent) return 0;
	return 1;	
}

static void acalc(struct entity *a, struct entity *b){
	
	a->hp -= a->attk;
	char *s = malloc(sizeof(char) * (500) );
	snprintf(s, 500, "%s hit %s", a->name, b->name);
	addMsg(s);
	free(s);
	chkDeath(b);
}

void attkEnt(enum direc d, struct entity *ent){
	struct tile *n = NULL;
	switch (d){
		case NORTH: 
			n = ent->loc->n;
			break;
		case SOUTH:
			n = ent->loc->s;
			break;
		case WEST:
			n = ent->loc->w;
			break;
		case EAST:
			n = ent->loc->e;
			break;
		default:
			return;
	}
	if(!n) return;
	if(!n->ent) return;
	acalc(ent, n->ent);

}

void mvEnt(enum direc d, struct entity *ent){
	struct tile *n = NULL;
	switch (d){
		case NORTH: 
			n = ent->loc->n;
			break;
		case SOUTH:
			n = ent->loc->s;
			break;
		case WEST:
			n = ent->loc->w;
			break;
		case EAST:
			n = ent->loc->e;
			break;
		default:
			return;
	}
	if(!n) return;
	if(n->base == WALL) return;
	if(n->ent != NULL) return;
	
	n->ent = ent;
	ent->loc->ent = NULL;
	ent->loc = n;
}

void doView(struct tile *t, unsigned char hop){
	t->vis = TRUE;
	t->saw = TRUE;
	if(!hop) return;
	if(t->base == WALL) return;
	doView(t->n, hop-1);
	doView(t->e, hop-1);
	doView(t->s, hop-1);
	doView(t->w, hop-1);
}

void makeLOS(struct dungeon *dgn){
	int x = 0;
	int y = 0;
	struct level *lvl = dgn->clvl;
	for(x = 0; x < lvl->w; x++){
		for(y = 0; y < lvl->h; y++){
			lvl->lvl[x][y].vis = FALSE;
		}
	}
	doView(dgn->p->loc, 4);	
}
