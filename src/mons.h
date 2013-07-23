/*
 * =====================================================================================
 *
 *       Filename:  mons.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/20/2013 08:43:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _MONS_H
#define _MONS_H

#include "dgn.h"

void load_mons();

void spawnStart(struct level *lvl);

void spawnCons(struct level *lvl);

void monsAct(struct dungeon *dgn, struct entity *e);

#endif
