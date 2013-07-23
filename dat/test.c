#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
int main(){
	FILE *fp = fopen("startUpMsg", "r");
	char buf[4096];
	while(!feof(fp)){
		fgets(buf, sizeof(buf), fp);
		puts(buf);

	}

	return 0;
}
