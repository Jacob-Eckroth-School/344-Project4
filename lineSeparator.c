#include "lineSeparator.h"
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "buffers.h"
#include "usefulFunctions.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
/*
** Description: Replaces all line separators '\n' in buffer 1 with ' ' and then transfers that data to buffer2
** Prerequisites: buffer2/buffer 1 are allocated
** Updated/Returned: buffer1 keeps being updated with data inputted by user until user says STOP
*/
void* separatorLoop(void* arg) {
	assert(buffer1);
	assert(buffer2);
	while (true) {
		pthread_mutex_lock(&buffer1Mutex);
		if (!buffer1Processing) {
			pthread_cond_wait(&buffer1DoneFilling,&buffer1Mutex);
		}
		
		transferBuffer1ToBuffer2();

		pthread_cond_signal(&buffer1DoneProcessing);
		buffer1Processing = false;
		pthread_mutex_unlock(&buffer1Mutex);

		//if we're done getting input, and everything is transferred over, then we exit this thread
		if (inputDone) {
			separatorDone = true;
			pthread_exit(NULL);
		}
	}
	return NULL;
}



/*
** Description: Transfers buffer 1 to buffer 2, replacing all \n with ' '
** Prerequisites: buffer2/buffer1 are allocated
** Updated/Returned: buffer2 holds the information that was in buffer1, but with spaces instead of newlines.
*/
void transferBuffer1ToBuffer2() {
	pthread_mutex_lock(&buffer2Mutex);
	//condition lock
	if (buffer2Processing) {
		pthread_cond_wait(&buffer2DoneProcessing,&buffer2Mutex);
	}

	
	//if there's a \n replace it with a space.
	for (int i = 0; i < strlen(buffer1) + 1; i++) {		//+1 to include the null terminator
		if (buffer1[i] == '\n') {
			buffer2[i] = ' ';
		}
		else {
			buffer2[i] = buffer1[i];
		}
	}

	//the plus sign thread will set this to be false.
	buffer2Processing = true;
	pthread_cond_signal(&buffer2DoneFilling);
	pthread_mutex_unlock(&buffer2Mutex);
}