/*
 * =====================================================================================
 *
 *       Filename:  level.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 03:46:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "dgn.h"
#include "alg/arr.h"
#include "term.h"
#include "logger.h"
#include "alg/rand.h"
#include <stdbool.h>

void drawTile(struct tile *t, int x,int y){
	if(!t->saw) return;

	if(t->vis){
		if(t->ent){
			putChar(x, y, t->ent->c, t->ent->col);
		}else if(t->base == WALL){
			putChar(x, y, '#', CGRAY);
		}else if(t->base == FLOOR){
			putChar(x, y, '.', CGRAY);
		}else if(t->base == STAIR_UP){
			putChar(x, y, '<', CGRAY);
		}else if(t->base == STAIR_DOWN){
			putChar(x, y, '>', CGRAY);
		}else if(t->base == FOUNTAIN){
			putChar(x, y, '%', CBLUE);
		}
	}else{
		if(t->base == WALL){
			putChar(x, y, '#', CWHITE);
		}else if(t->base == FLOOR){
			putChar(x, y, '.', CWHITE);
		}else if(t->base == STAIR_UP){
			putChar(x, y, '<', CWHITE);
		}else if(t->base == STAIR_DOWN){
			putChar(x, y, '>', CWHITE);
		}else if(t->base == FOUNTAIN){
			putChar(x, y, '%', CBLUE);
		}
	}
}

void displayLevel(struct level *lvl){
	int x = 0, y = 0;
	for(x = 0; x < lvl->w; x++){
		for(y = 0; y < lvl->h; y++){
			drawTile(&lvl->lvl[x][y], x, y);
		}
	}
}


void delLvl(struct level *lvl){
	if(lvl){
		if(lvl->lvl){
			int i = 0;
			for(i = 0; i < lvl->w; i++){
				free(*(lvl->lvl+i));
			}
			free(lvl->lvl);	
		}
		free(lvl);
	}
}

