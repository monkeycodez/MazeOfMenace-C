/*
 * =====================================================================================
 *
 *       Filename:  logger.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 02:25:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

FILE* f;

void endl(void){
	fclose(f);
}

void startl(){
	atexit(endl);
	f = fopen(LOG_FILE, "w");
}

void _log_add(char *a, ...){
	va_list argptr;
	va_start(argptr, a);
	vfprintf(f, a, argptr);
	va_end(argptr);
}
