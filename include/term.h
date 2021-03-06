/*
 * =====================================================================================
 *
 *       Filename:  term.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/21/2013 05:37:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */



#ifndef _TERM_H
#define _TERM_H
#include <ncurses.h>

#define X_DISP_SIZE 	90
#define Y_DISP_SIZE 	60

#define MSG_WSTART 	33

#define CWHITE 		1
#define CRED 		2
#define CGREEN 		3
#define CYELLOW 	4
#define CBLUE 		5
#define CCYAN 		6
#define CMAGENTA	7

#define CORANGE 	8
#define CORB 		9
#define CGRAY 		10

#define CWHITE_S	"$CWHITE"
#define CRED_S 		"$CRED"
#define CGREEN_S	"$CGREEN"
#define CYELLOW_S	"$CYELLOW"
#define CBLUE_S		"$CBLUE"
#define CCYAN_S		"$CCYAN"
#define CMAGENTA_S	"$CMAGENTA"
#define CORANGE_S	"$CORANGE"
#define CORB_S		"$CORB"
#define	CGRAY_S		"$CGRAY"

#define ORB_C		-1

/*
 *functions
 */

void initEnv();
void endEnv();
void putChar(int x, int y, int c, int colNum);
void putStringWithAttrib(const char *str, int xStart, int yStart);
void displayScr();
void clearScr();


/*
 * 0 = start
 * 1 = normal
 * 2 = dead
 */
extern  int gameState;

#endif
