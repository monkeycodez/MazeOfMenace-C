/*
 * =====================================================================================
 *
 *       Filename:  logger.c
 *
 *    Description:  
 *
 r        Version:  1.
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


FILE *_get_logfile(char *file){
	static FILE* f = NULL;
	if(!f){ 
		f = fopen(file, "a");
		if(!f) exit(-1);
	}
	return f;
}
