#include "usefulFunctions.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

/*
** Description: Gets the length of a number, i.e 1000 returns 4, 0 returns 1, 20 returns 2
** Prerequisites: None
** Updated/Returned: Returns the length of a number as if it were a string
*/
int getLengthOfNumber(int number) {
	return (number == 0) ? 1 : floor(log10(abs(number))) + 1;
}

/*
** Description: Gets string input from a user, with a size of bufsize
** Prerequisites: Prompt is allocated
** Updated/Returned: Returns a pointer to the user entered string
*/
void debugBuffer(char* buffer) {
		printf("Full Dec of inputted buffer: \n");
		for (int i = 0; i < strlen(buffer); i++) {
			printf("%c, correlates to: %d , ",buffer[i], buffer[i]);
		}
		printf("\n");
	
}

