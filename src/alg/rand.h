/*
 * =====================================================================================
 *
 *       Filename:  rand.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 08:58:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef _RAND_H
#define _RAND_H

#include <stdlib.h>


/* get random number from (0,A) inclusive*/
#define R_INT_M(A) (rand() % (A+1))

/* get random number from A-B inclusive
 * precog: B > A , A may be negative
 */
#define R_INT_R(A, B) (rand() % (B+1-A) + A)



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dice_roll
 *  Description:  Simulate multiple dice rolls with NdS +P format where:
 *  		N is the number of dice
 *  		S is the sides of each dice
 *  		P is the number to add to the result
 * =====================================================================================
 */
static inline int dice_roll(int n, int s, int p){
	int i = 0;
	int t = 0;
	while(i < n){
		t += R_INT_R(1, s);		
		i++;
	}
	return t+p;
}


#endif
