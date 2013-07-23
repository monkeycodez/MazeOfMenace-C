/*
 * =====================================================================================
 *
 *       Filename:  arr.h
 *
 *    Description:  Header for some useful array fuctions/macros
 *
 *        Version:  1.0
 *        Created:  07/18/2013 03:07:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _ARR_H
#define _ARR_H

#include <stdlib.h>



#define NEW_2D_ARR(S, W, H, A) int i = 0; \
		void *INNER_A = calloc(W * H, S); 	\
	        A = calloc(W, sizeof(void *));  	\
       	 	for(; i < W; i++) {            		\
			A[i] = &INNER_A[i*H];} \



#define DEL_2D_ARR(A) do{ \
	free(*A); \
	free(A); \
}while(0);

#endif
