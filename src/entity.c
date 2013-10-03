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
#include "alg/rand.h"
#include "term.h"

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
	if(i == NULL) return;
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
		darray_clear(t->itm);
	}
	return in;
}

void addItoT(struct tile *t, union item *i){
	if(t->itm == NULL){
		t->itm = darray_new2i(5, 5);
	}
	darray_add(t->itm, i);
}

int chkDeath(struct entity *ent){
	if(ent->hp <= 0){
		if(dice_roll(3, 6, 0) > 10){
			union item *i = malloc(sizeof(union item));
			i->c.type = I_CHEST;
			i->c.name = "armor";
			i->c.disp = '(';
			i->c.col = CGREEN;
			i->c.based = 3;
			i->c.ev = 0;
			addItoT(ent->loc, i);
		}
		ent->loc->ent = NULL;
		ent->loc = NULL;
		ent->dead = 1;
		if(ent->list)
			darray_remove(ent->list, darray_search(ent->list, ent));
		return ent->expamt;
	}
	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  canMove
 *  Description:  Determins if an entity can move in direction d
 *  		returns 0 if false, !0 if true
 * =====================================================================================
 */
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
	if(!n) return 0;
	if(n->base == WALL) return 0;
	if(n->ent) return 0;
	return 1;
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

static void lvl_up(struct entity *a){
	if(a->exp >= (a->lvl*a->lvl)*3){
		a->exp = 0;
		a->lvl++;
		a->attk += 2;
		a->hpmax += 10;
		a->hp = a->hpmax;
		a->def++;
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  acalc
 *  Description:  does damage caluclations and checks defenders death
 *  		a - attacker
 *  		b - defender
 * =====================================================================================
 */
static void acalc(struct entity *a, struct entity *b){
	int dmg = a->attk - b->def;
	dmg = dmg > 0 ? dmg : 0;
	b->hp -= dmg;
	char *s = malloc(sizeof(char) * (500) );
	snprintf(s, 500, "%s hit %s", a->name, b->name);
	addMsg(s);
	free(s);
	int i = chkDeath(b);
	a->exp += i;
	lvl_up(a);
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  attkEnt
 *  Description:  attackes an entity in direc d.  acalc is used for damage calc
 *  		d - direction to attack in
 *  		ent - attacker
 * =====================================================================================
 */
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


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  mvEnt
 *  Description:  moves entity ent in direction d if possible. not possible
 *  			if newloc is NULL or is wall;
 * =====================================================================================
 */
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
