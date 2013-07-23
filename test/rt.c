/*
 * =====================================================================================
 *
 *       Filename:  rt.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/19/2013 09:48:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "rand.h"
#include <stdio.h>

int main(){
	int i = 0;
	while(i < 30){
		i++;
	}
	i = 0;
	while(i < 50){
		printf("B: %d\n", R_INT_R(-50, 50));
		i++;
	}
}
