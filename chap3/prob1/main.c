#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char longest[MAXLINE];

int main(void){
	int len, max = 0;

	while(fgets(line,MAXLINE,stdin) != NULL) {
		len = strlen(line);

		if(len > max) {
			max = len;
			copy(line, longest);
		}
	}

		printf("%s", longest);

	return 0;
}
