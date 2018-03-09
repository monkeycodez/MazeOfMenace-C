/*
 * =============================================================================
 *
 *       Filename:  main.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/12/2016 05:27:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =============================================================================
 */

#ifndef _MAIN_H
#define _MAIN_H

#include "alg/linkedlist.h"
#include "dgn.h"

struct controls;

typedef void (*control_f)();

struct controls{
	control_f 
		input_f,
		logic_f,
		draw_f;
	void *data, 
	*i, *l, *d; /* extra data for the 3 funcs */
};

typedef struct controls controls;

extern controls ctrls;
extern int is_running;
void set_end();

void sstr_draw();
void dummy_f();    
void wait_any_key_f();
extern void (*after_waitk)(int key);
void setup_sstr(char *file, void (*cb)(int key));

void startup_game();
void mloop();

char* readFile(char *file);

extern struct dungeon *gdgn;

#endif


