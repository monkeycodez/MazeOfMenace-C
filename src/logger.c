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


void _log_add(char *file, char *msg, ...){
	FILE* f = fopen(file, "a");
	if(!f) exit(-1);
	va_list argptr;
	va_start(argptr, msg);
	vfprintf(f, msg, argptr);
	va_end(argptr);
	fflush(f);
	fclose(f);
}
