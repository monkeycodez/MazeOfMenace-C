/*
 * =====================================================================================
 *
 *       Filename:  generate.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/20/2013 04:44:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "dgn.h"
#include "alg/rand.h"
#include "mons.h"
#include "alg/darray.h"

void getRandLoc(struct level *lvl, int *x, int *y){
	*x = R_INT_M(lvl->w - 1);
	*y = R_INT_M(lvl->h - 1);
	while(lvl->lvl[*x][*y].base != FLOOR){
		*x = R_INT_M(lvl->w - 1);
		*y = R_INT_M(lvl->h - 1);	
	}
}

static void a1_mkrm(struct level *lvl, int x0, int y0, int x1, int y1){
	int x = x0;
	int y = y0;
	for(x = x0; x < x1; x++){
		for(y = y0; y < y1; y++){
			lvl->lvl[x][y].base = FLOOR;
		}
	}
}

static void a1_mkcorr(struct level *lvl, int x0, int y0, int x1, int y1){
	if(dice_roll(3, 6, 1) >= 7){
		//make e corr
		int yloc = R_INT_R(y0, y1 - 1);
		int x = x1;
		int y = yloc;
		while(x < lvl->w - 1 && lvl->lvl[x][y].base == WALL){
			lvl->lvl[x][y].base = FLOOR;
			x++;
		}
	}
	if(dice_roll(3, 6, 1) >= 9){
		//make n corr
		int xloc = R_INT_R(x0, x1);
		int x = xloc;
		int y = y0 - 1;
		while(y > 0 && lvl->lvl[x][y].base == WALL){
			lvl->lvl[x][y].base = FLOOR;
			y--;
		}
	}
}

void static a1_rmDiv(struct level *lvl, int x0, int y0, int x1, int y1, int dph){
//	log_info(" roomdiv: x0 = %d, y0 = %d, x1 = %d, y1 = %d \n", x0, y0, x1, y1);
	if(!dph){
		if(dice_roll(3, 6, 0) <= 7) return;
		int xs0 = x0 + 1 + R_INT_M(4);
		int ys0 = y0 + 1 + R_INT_M(4);
		int xs1 = x1 - 1 - R_INT_M(3);
		int ys1 = y1 - 1 - R_INT_M(3);
		a1_mkrm(lvl, xs0, ys0, xs1, ys1);
		a1_mkcorr(lvl, xs0, ys0, xs1, ys1);
		return;
	}
	if(x1 - x0 > y1 - y0){
		//SPLit width 
		int xhalf = (x1 + x0) / 2;
		a1_rmDiv(lvl, x0, y0, xhalf, y1, dph - 1);
		a1_rmDiv(lvl, xhalf, y0, x1, y1, dph - 1);
	}else{
		//split len
		int yhalf = (y1 + y0) / 2;
		a1_rmDiv(lvl, x0, y0, x1, yhalf, dph - 1);
		a1_rmDiv(lvl, x0, yhalf, x1, y1, dph - 1);
	}
}


static void a1_createRooms(struct level *lvl){
	int xhalf = lvl->w / 2 + R_INT_R(-3, 3);
	a1_rmDiv(lvl, 0, 0, xhalf, lvl->h, 2);
	a1_rmDiv(lvl, xhalf, 0, lvl->w, lvl->h, 2);
}

static void a_createTiles(struct level *lvl){
	lvl->lvl = malloc(sizeof(struct tile *) * lvl->w);
	int i = 0;
	for(i = 0; i < lvl->w; i++){
		*(lvl->lvl+i) = malloc(sizeof(struct tile) * lvl->h);
	}
	int x = 1, y = 0;
	for(x = 1; x < lvl->w; x++){
		for(y = 0; y < lvl->h; y++){
			lvl->lvl[x-1][y].w = &(lvl->lvl[x][y]);
			lvl->lvl[x][y].e = &(lvl->lvl[x-1][y]);
		}
	}
	for(y = 1; y < lvl->h; y++){
		for(x = 0; x < lvl->w; x++){
			lvl->lvl[x][y-1].s = &(lvl->lvl[x][y]);
			lvl->lvl[x][y].n = &(lvl->lvl[x][y-1]);
		}
	}
	for(x = 0; x < lvl->w; x++){
		for(y = 0; y < lvl->h; y++){
			lvl->lvl[x][y].base = WALL;
			lvl->lvl[x][y].x = x;
			lvl->lvl[x][y].y = y;
			lvl->lvl[x][y].ent = NULL;
			lvl->lvl[x][y].vis = FALSE; 
			lvl->lvl[x][y].itm = NULL;
			lvl->lvl[x][y].saw = FALSE; 
		}
	}
}

static void a1_mkStairs(struct level *lvl){
	int x = R_INT_M(lvl->w - 1);
	int y = R_INT_M(lvl->h - 1);
	while(lvl->lvl[x][y].base != FLOOR){
		x = R_INT_M(lvl->w - 1);
		y = R_INT_M(lvl->h - 1);	
	}
	lvl->sup = &lvl->lvl[x][y];
	lvl->sup->base = STAIR_UP;
	log_info("stair up: lvl = %d, x = %d, y = %d\n", lvl->depth, x, y);
	x = R_INT_M(lvl->h - 1);
	y = R_INT_M(lvl->h - 1);
	while(lvl->lvl[x][y].base != FLOOR){
		x = R_INT_M(lvl->w - 1);
		y = R_INT_M(lvl->h - 1);	
	}
	lvl->sdw = &lvl->lvl[x][y];
	lvl->sdw->base = STAIR_DOWN;
	
}

static void a1_mkFountains(struct level *lvl){
	int nf = R_INT_R(1, 5);
	int x = 0, y = 0;
	int i = 0;
	while(i < nf){
		while(lvl->lvl[x][y].base != FLOOR){
			x = R_INT_M(lvl->w - 1);
			y = R_INT_M(lvl->h - 1);
		}
		lvl->lvl[x][y].base = FOUNTAIN;
		i++;
	}
}

static void a1_cr(struct level *lvl){
	a_createTiles(lvl);
	a1_createRooms(lvl);
	a1_mkStairs(lvl);
	a1_mkFountains(lvl);
	spawnStart(lvl);
}

void getRandTtype(struct level *lvl, int *x, int *y, int ttype){
	*x = R_INT_M(lvl->w - 2) + 1;
	*y = R_INT_M(lvl->h - 2) + 1;
	while(lvl->lvl[*x][*y].base != ttype){
		*x = R_INT_M(lvl->w - 2) + 1;
		*y = R_INT_M(lvl->h - 2) + 1;	
	}
}

static int b1_wallct1(struct tile *t){
	int w = 0;
	if(t->n->base == WALL) w++;
	if(t->s->base == WALL) w++;
	if(t->w->base == WALL) w++;
	if(t->e->base == WALL) w++;
	if(t->e->n->base == WALL) w++;
	if(t->e->s->base == WALL) w++;
	if(t->w->n->base == WALL) w++;
	if(t->w->s->base == WALL) w++;
	return w;
}


static int b1_wallct(struct tile *t, struct level *lvl, int r){
	int w = 0;
	int x = t->x - r, y = t->y - r;
	x = x < 0 ? 0 : x;
	y = y < 0 ? 0 : x;
	int y1 = y;
	for(; x < t->x + r && x < lvl->w; x++){
		for(y = y1; y < t->y + r && y < lvl->h; y++){
			if(lvl->lvl[x][y].base == WALL){
				w++;
			}
		}
	}
	if(t->base == WALL) w--;
	return w;
}


static void b1_erode(struct level *lvl){
	//start off with several random rooms
	int x = 0, y = 0;
	for(x = 1; x < lvl->w - 1; x++){
		for(y = 1; y < lvl->h - 1; y++){
			if( rand() % 100 < 45){
				lvl->lvl[x][y].base = FLOOR;
			}
		}
	}
	int c = 0;
	for(c = 0; c < 5; c++){
		for(x = 1; x < lvl->w - 1; x++){
			for(y = 1; y < lvl->h - 1; y++){
				int wc = b1_wallct1(&lvl->lvl[x][y]);
				if(wc >= 5){
					lvl->lvl[x][y].base = WALL;
				}
				wc = b1_wallct(&lvl->lvl[x][y], lvl, 2);
				if(wc == 0){
					lvl->lvl[x][y].base = WALL;
				}
			}
		}	
	}

}

static void b1_cr(struct level *lvl){
	a_createTiles(lvl);
	b1_erode(lvl);
	a1_mkStairs(lvl);
}

struct level *createLvl(int depth){
	struct level *lvl = malloc(sizeof(struct level));
	lvl->depth = depth;
	lvl->up = NULL;
	lvl->down = NULL;
	lvl->w = DEF_LVL_X;
	lvl->h = DEF_LVL_Y;
	lvl->mons = darray_new();

	a1_cr(lvl);

	return lvl;	
}


