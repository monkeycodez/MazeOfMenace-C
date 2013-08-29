/*
 * =====================================================================================
 *
 *       Filename:  mons.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/20/2013 08:42:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <string.h>
#include <stdlib.h>
#include "dgn.h"
#include "mons.h"
#include "alg/darray.h"
#include "alg/rand.h"
#include "logger.h"
#include "e_template.h"

struct darray *mons;

int mons_range = 3;
int mons_r_mid = 0;

void add_mons(struct e_temp *e){
	darray_add(mons, e);
}

void load_mons(){
	//TODO: make actual mons loading
	
	mons = darray_new();
	parseEnts();
		
}

void putMons(struct level *lvl, struct e_temp *ent, int x, int y){
	struct entity *e = calloc(1, sizeof(struct entity));
	struct tile *t = &lvl->lvl[x][y];
	t->ent = e;
	e->loc = t;
	e->list = lvl->mons;
	darray_add(lvl->mons, e);
	e->name = strdup(ent->name);
	e->hpmax = R_INT_R(ent->hpmin, ent->hpmax);
	e->hp = e->hpmax;
	e->attk = R_INT_R(ent->attkmin, ent->attkmax);
	e->def = R_INT_R(ent->defmin, ent->defmax);
	e->speed = 50;
	e->scount = e->speed;
	e->c = ent->disp;
	e->col = ent->color;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getRDepthMons
 *  Description:  returns a random monster template from within the parameters
 *  		
 *  		minimum depth of mons = depth - (range/2 + middle)
 *  		maximum depth of mons = depth + (range/2 + middle)
 *  		so depth = 10, range = 4, middle = 1 will return a template with
 *  		a depth between 9 and 13, inclusive
 * =====================================================================================
 */
struct e_temp *getRDepthMons(int depth, int range, int middle){
	int size = darray_usize(mons);
	int min_d = depth - (range/2 + middle);
	int max_d = depth + (range/2 + middle);
	struct e_temp *ret = NULL, *t;
	while(!ret){
		int i = R_INT_M(size);
		t = darray_get(mons, i);
		if(t && t->depth >= min_d && t->depth <= max_d){
			ret = t;
		}
	}

	
	return ret;
}

void spawnStart(struct level *lvl){
	int numm = dice_roll(lvl->depth + 3, 6, 0);
	int i = 0;
	int x = 0, y = 0;
	while(i < numm){
		struct e_temp *fr = getRDepthMons(lvl->depth, 4, 1);
		getRandLoc(lvl, &x, &y);
		putMons(lvl, fr, x, y);
		i++;		
	}
}


static int getpd(struct dungeon *dgn, struct tile *tl, int h){
	if(h == 0) return 0;
	if(tl->ent == dgn->p) return h;
	if(tl->base == WALL) return 0;
	int e, s, w, n;
	e = getpd(dgn, tl->e, h-1);
	w = getpd(dgn, tl->w, h-1);
	n = getpd(dgn, tl->n, h-1);
	s = getpd(dgn, tl->s, h-1);
	int r = s > n ? s : n ;
	r = r > e ? r : e ;
	r = r > w ? r : w ;
	return r;
}

enum direc getPDir(struct dungeon *dgn, struct tile *tl){
	int e, n, s, w;
	e = getpd(dgn, tl->e, 4);
	w = getpd(dgn, tl->w, 4);
	s = getpd(dgn, tl->s, 4);
	n = getpd(dgn, tl->n, 4);
	if(e + n + s + w == 0) return -1;

	if(e >= n && e >= s && e >= w)  return EAST;
	if(n >= e && n >= s && n >= w)  return NORTH;
	if(s >= n && s >= e && s >= w)  return SOUTH;
	if(w >= n && w >= s && w >= e)  return WEST;
	return  -1;
}

enum direc randMV(){
	return R_INT_M(3);
}

void monsAct(struct dungeon *dgn, struct entity *e){
	int dir = getPDir(dgn, e->loc);
	if(dir == -1){
		enum direc i = randMV();
		int c = 0;
		while(!canMove(i, e) && c < 50){
			i = randMV();
			c++;
		}
	//	log_info("moving entity %s %d", e->name, i);
		mvEnt(i, e);
	}else{
		if(canMove(dir, e)){
			mvEnt(dir, e);
		}else if(canAttk(dir, e)){
			attkEnt(dir, e);
		}
	}
}
