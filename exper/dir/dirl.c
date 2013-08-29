/*
 * =====================================================================================
 *
 *       Filename:  dirl.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/2013 10:02:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matthew Gruda (mg), matthewgruda@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

int main(){
	DIR *up;
	struct dirent *dir;
	char *cdr = getcwd(NULL, 0);
	printf("%s\n", cdr);
	up = opendir("..");
	while(dir = readdir(up)){
		puts(dir->d_name);
	}
	closedir(up);

}
