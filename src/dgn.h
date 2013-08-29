/*
 * =====================================================================================
 *
 *       Filename:  dgn.h
 *
 *    Description:  level definitions
 *
 *        Version:  1.0
 *        Created:  07/19/2013 02:58:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _DGN_H
#define _DGN_H

#include "alg/darray.h"

#define DEF_LVL_X 70
#define DEF_LVL_Y 25

#define WALL 1
#define FLOOR 2
#define STAIR_UP 3
#define STAIR_DOWN 4
#define FOUNTAIN 5

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

struct dungeon;

enum direc{
	NORTH, SOUTH,
	EAST, WEST,
	DRINK, WAIT,
	GET
};

struct weapon{
	short type;
	char *name;
	int basea;
	int toHit;
	int wepp;
};

struct a_chest{
	short type;
	char *name;
	int based;
	int ev;
};

struct consume{
	short type;
	char *name;
	int cnt;
	int pow;
	int (*cons_use_f)(struct dungeon *dgn, int pow);
};

#define I_WEP 1
#define I_CHEST 2

union item{
	short type;
	struct weapon w;
	struct a_chest c;
	struct consume i;
};

struct entity{
	char *name;
	char dead;
	int    hp,
	       hpmax,
	       attk,
	       def,
	       speed,
	       scount;
	//attribs
	int str;  //attack bonus
	int cons; //defense bonus 
	int dex;  //evade attk
	
	//skills
	char uncmb,
	     fight,
	     sword,
	     armr;

	struct tile *loc;
	char c;
	int col;
	struct darray *list;
	struct darray *inv;
	union item *wep;
	union item *chest;	
};

struct tile{
	struct tile *n, *e, *s, *w;
	int x, y;
	int vis, saw;
	int base;
	struct entity *ent;
	struct darray *itm;
};

struct level{
	struct level *up, *down;
	int depth;
	struct tile **lvl;
	int w, h;
	struct tile *sup;
	struct tile *sdw;
	struct darray *mons;
};

struct dungeon{
	struct entity *p;
	int mdepth;
	struct darray *lvls;
	struct level *clvl;
};

struct dungeon *initDgn();

void delDgn(struct dungeon *dgn);

struct level *createLvl(int depth);

void displayDungeon(struct dungeon *dgn);

void displayLevel(struct level *lvl);

void delLvl(struct level *lvl);

void mvEnt(enum direc d, struct entity *ent);

void makeLOS(struct dungeon *dgn);

void getRandLoc(struct level *lvl, int *x, int *y);

int canMove(enum direc d, struct entity *ent);

int canAttk(enum direc d, struct entity *ent);

void attkEnt(enum direc d, struct entity *ent);

void equipItm(struct entity *e, union item *i);

void addToInv(struct entity *e, union item *i);

union item *rmFromInv(struct entity *e, union item *i);

union item *getItem(struct tile *t, union item *i);

#endif

