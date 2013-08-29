/*
 * =====================================================================================
 *
 *       Filename:  dgn.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 03:41:56 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "dgn.h"
#include "term.h"
#include "turn.h"

void displayDungeon(struct dungeon *dgn){
	makeLOS(dgn);
	displayLevel(dgn->clvl);
	displayBar(dgn);
}

struct dungeon *initDgn(){
	struct dungeon *dgn = malloc(sizeof(struct dungeon));
	if(!dgn) return NULL;
	dgn->mdepth = 0;
	dgn->lvls = darray_new();
	struct level *lvl = createLvl(0);
	darray_add(dgn->lvls, lvl);
	dgn->clvl = lvl;
	dgn->p =  malloc ( sizeof(struct entity) );
	if ( dgn->p == NULL ) {
		fprintf(stderr, "\ndynamic memory allocation failed\n" );
		exit(EXIT_FAILURE);
	}
	dgn->p->name = "you";
	dgn->p->c = '@';
	dgn->p->col = CBLUE;
	dgn->p->attk = 6;
	dgn->p->def = 1;
	dgn->p->dead = 0;
	dgn->p->list = NULL;
	dgn->p->speed = 60;
	dgn->p->inv = darray_new();
	dgn->p->hp = 100;
	dgn->p->hpmax = 100;
	dgn->p->loc = lvl->sup;
	lvl->sup->ent = dgn->p;

	return dgn;
}

void delDgn(struct dungeon *dgn){
	if(!dgn) return;
	int i = 0;
	if(dgn->lvls){
		for(i = 0; i < darray_usize(dgn->lvls); i++){
			delLvl(darray_get(dgn->lvls, i));
		}
		darray_del(dgn->lvls);
	}
	if(dgn->p) free(dgn->p);
	
	free(dgn);
}
