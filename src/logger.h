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

/* 
 * ===  MACRO  =========================================================================
 *         Name:  LOG_FILE
 *  Description:  string for where a logfile will be sent.
 *  			users may redefine this
 * =====================================================================================
 */
#ifndef LOG_FILE
#define LOG_FILE "mazeofmenace.log"
#endif

#define STR_ERRNO (errno == 0 ? "None" : strerror(errno)) 

#ifndef NDEBUG
/*  General logging macros, prints to LOG_FILE, turned of with NDEBUG */
#define log_info(A, ...) _log_add(LOG_FILE, "[INFO]: " A, __VA_ARGS__)
#define log_warn(A, ...) _log_add(LOG_FILE, "[WARNING]: " A, __VA_ARGS__)
#define log_error(A, ...) _log_add(LOG_FILE, "[ERROR]: (%s, %d, errnor: %s ) " A "\n", __FILE__, __LINE__, STR_ERRNO, __VA_ARGS__)
#define log_add(A, ...) _log_add(LOG_FILE, A, __VA_ARGS__)

#else

#define log_info(A, ...)
#define log_warn(A, ...)
#define log_error(A, ...)
#define log_add(A, ...)

#endif

#define CHECK_MEM(A) 




void _log_add(char *file, char *a, ...);



#endif
