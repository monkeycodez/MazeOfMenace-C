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

void startl();

#define LOG_FILE "mazeofmenace.log"

#ifndef NDEBUG
#define log_info(A, ...) _log_add("[INFO]: " A, __VA_ARGS__)
#define log_warn(A, ...) _log_add("[WARNING]: " A, __VA_ARGS__)
#define log_error(A, ...) _log_add("[ERROR]: " A, __VA_ARGS__)
#define log_add(A, ...) _log_add(A, __VA_ARGS__)
#else
#define log_info(A, ...)
#define log_warn(A, ...)
#define log_error(A, ...)
#define log_add(A, ...)
#endif

void _log_add(char *a, ...);

#endif
