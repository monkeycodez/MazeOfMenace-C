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

//struct key_event{
	//int code;
//}; 

//typedef struct key_event key_event;

//typedef struct key_event *(*get_event_cb)(void *inp_dev);
//typedef int (*init_in_sys_cb)(void **in_dev);

//struct key_event *get_event_nc(void *n);
//int init_in_sys_nc(void **n);


//Old Stuff


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initI
 *  Description:  Initalizes the input system
 * =====================================================================================
 */
void initI();

//int startLoop();

//int mainLoop(struct dungeon *dgn);

void dg_showd();
void dg_input();
void in_keysink();


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getKch
 *  Description:  gets input and returns it or returns NRESTART if it is a 
 *  			die key
 * =====================================================================================
 */
//int getKch();

#define RESTARTN 255
#define CONT 254
#define NRESTART 0
#define DEATH_FILE "dat/deathMsg"

#define CTRL_C_K 3

#endif
