#include "output.h"
#include <stdbool.h>
#include <pthread.h>
#include "buffers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
/*
** Description: Outputs buffer3 to stdout if it has more than OUTPUT_LINE_LENGTH characters in it, otherwise keeps waiting.
** Prerequisites: buffer 3 is allocated
** Updated/Returned: buffer3 might be updated to remove characters from the beginning in OUTPUT_LINE_LENGTH chunks
*/
void* outputLoop(void* arg) {
	assert(buffer3);
	while (true) {
		pthread_mutex_lock(&buffer3Mutex);

		//if buffer3Index hasn't increased, then we should wait for buffer 2 to transfer to buffer3
		if(buffer3Index < OUTPUT_LINE_LENGTH)
		{
			pthread_cond_wait(&buffer3DoneFilling, &buffer3Mutex);
		}


		outputBuffer3();


		pthread_cond_signal(&buffer3DoneProcessing);
		
		pthread_mutex_unlock(&buffer3Mutex);
		if (separatorDone) {
			pthread_exit(NULL);
		}
	}
	
}
/*
** Description: Outputs buffer3 to stdout in OUTPUT_LINE_LENGTH chunks with newline separation
** Prerequisites: buffer 3 is allocated
** Updated/Returned: buffer3 is updated to have OUTPUT_LINE_LENGTH characters/less, buffer3Index is updated to be the spot for the next character.
*/
void outputBuffer3() {
	int printIndex = 0;

	//while there are 80 characters to output
	while (buffer3Index - printIndex >= OUTPUT_LINE_LENGTH) {
		
		write(1, (buffer3 + printIndex), OUTPUT_LINE_LENGTH);
		write(1, "\n", 1);
		printIndex += OUTPUT_LINE_LENGTH;

	}
	

	int charsLeft = buffer3Index - printIndex;

	//copying all the remaining characters to the beginning of buffer3.
	for (int i = 0; i < charsLeft; i++) {
		buffer3[i] = buffer3[buffer3Index - charsLeft + i];
	}
	buffer3Index = charsLeft;

}