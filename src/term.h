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

#define X_DISP_SIZE 90
#define Y_DISP_SIZE 60

#define MSG_WSTART 33

#define CWHITE 1
#define CRED 2
#define CGREEN 3
#define CYELLOW 4
#define CBLUE 5
#define CCYAN 6
#define CMAGENTA 7

#define CORANGE 8
#define CORB 9
#define CGRAY 10


/*
 *functions
 */

void initEnv();
void endEnv();
void putChar(int x, int y, char c, int colNum);
void putStringWithAttrib(char *str, int xStart, int yStart);
void displayScr();
void clearScr();


/*
 * 0 = start
 * 1 = normal
 * 2 = dead
 */
extern  int gameState;

#endif
