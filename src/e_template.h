/*
 * =====================================================================================
 *
 *       Filename:  e_template.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/18/2013 05:43:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _E_TEMPLATE_H
#define _E_TEMPLATE_H

#include <stdint.h>

//a template for entitys
struct e_temp{
	char *name;
	uint32_t e_id;
	int depth;
	int hpmax, hpmin;
	int attkmax, attkmin;
	int defmax, defmin;
	char disp;
	int color;
};

#define HPMAX_S 	"hpmax"
#define HPMIN_S 	"hpmin"
#define ATTKMIN_S	"attkmin"
#define ATTKMAX_S	"attkmax"
#define DEFMAX_S 	"defmax"
#define DEFMIN_S 	"defmin"
#define DEPTH_S		"depth"
#define DISP_S		"char"
#define COL_S		"color"

void parseEnts();

#endif
