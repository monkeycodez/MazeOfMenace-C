/*
 * =====================================================================================
 *
 *       Filename:  logger.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 02:18:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _LOGGER_H
#define _LOGGER_H

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* 
 * ===  MACRO  =========================================================================
 *         Name:  LOG_FILE
 *  Description:  string for where a logfile will be sent.
 *  			users may redefine this
 * =====================================================================================
 */
#ifndef LOG_FILE
#define LOG_FILE _get_logfile("mmc.log")
#endif



#define STR_ERRNO (errno == 0 ? "None" : strerror(errno)) 

#ifndef NDEBUG
/*  General logging macros, prints to LOG_FILE, turned of with NDEBUG */
#define log_info(A, ...) flog_ap(LOG_FILE, "[INFO]: " A, ##__VA_ARGS__)
#define log_warn(A, ...) flog_ap(LOG_FILE, "[WARNING]: " A, ##__VA_ARGS__)
#define log_error(A, ...) flog_ap( \
		LOG_FILE, "[ERROR]: (%s, %d, errnor: %s ) "\
		A, __FILE__, __LINE__, STR_ERRNO, ##__VA_ARGS__)

#define log_add(A, ...) flog_ap(LOG_FILE, A, ##__VA_ARGS__)

#else

#define log_info(A, ...)
#define log_warn(A, ...)
#define log_error(A, ...)
#define log_add(A, ...)

#endif

#define flog_ap(F,  ...) _log_append(F, ##__VA_ARGS__)



#define CHECK_MEM(A) 

static inline void _log_append(FILE *f, char *a, ... ){
	va_list argptr;
	va_start(argptr, a);
	vfprintf(f, a, argptr);
	va_end(argptr);
	fputc('\n', f);
	fflush(f);
}



FILE *_get_logfile(char *file);

static inline void _close_log(){
	fclose(LOG_FILE);
}


#endif
