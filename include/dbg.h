#ifndef  _DBG_H
#define  _DBG_H

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "logger.h"

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define check(A, M, ...) if(!(A)) { log_error(M, ##__VA_ARGS__); \
			errno=0; exit(-1); }

#define check_mem(A) check(A, "Out of memory.%s", "")

#ifndef NDEBUG
#define check_debug(A, M, ...) if(!(A)) { log_add(M, ##__VA_ARGS__); \
	errno=0; exit(-1); }
#else
#define check_debug(A, M, ...)
#endif

#endif

