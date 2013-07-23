/*
 * =====================================================================================
 *
 *       Filename:  input.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 01:48:52 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _INPUT_H
#define _INPUT_H

#include "dgn.h"

void initI();

int startLoop();

int mainLoop(struct dungeon *dgn);

#define NRESTART 255
#define RESTARTN 1
#define DEATH_FILE "dat/deathMsg"

#endif
