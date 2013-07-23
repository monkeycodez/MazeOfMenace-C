/*
 * =====================================================================================
 *
 *       Filename:  turn.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/20/2013 12:52:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  _TURN_H
#define  _TURN_H

#include "dgn.h"

#define WIN_MV 2
#define ESC_DGN 3

void turnp(enum direc d, struct dungeon *dgn);

int go_up(struct dungeon *dgn);

void go_down(struct dungeon *dgn);

void displayBar(struct dungeon *dgn);

void addMsg(char *msg);

#endif   
