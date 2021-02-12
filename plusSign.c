#include "plusSign.h"
#include <stdlib.h>
#include <stdbool.h>
#include "buffers.h"
#include <pthread.h>
#include <string.h>
#include "usefulFunctions.h"
#include <stdio.h>
#include <assert.h>

/*
** Description: Loops infinitely until told to stop by previous thread, transferring data from buffer2 to buffer3
** Prerequisites: buffer 3 is allocated, buffer2 is allocated
** Updated/Returned: data is transfered into buffer3 from buffer2 with ++'s replaced.
*/
void* plusLoop(void* arg) {
	assert(buffer3);
	assert(buffer2);
	while (true) {
		pthread_mutex_lock(&buffer2Mutex);
		if (!buffer2Processing) {
			pthread_cond_wait(&buffer2DoneFilling, &buffer2Mutex);
		}

		transferBuffer2ToBuffer3();


		//we're done processing buffer2.
		pthread_cond_signal(&buffer2DoneProcessing);
		buffer2Processing = false;
		pthread_mutex_unlock(&buffer2Mutex);

		//if we're done separating lines, then we're done transferring them, so we exit. 
		if (separatorDone) {
			plusDone = true;
			pthread_exit(NULL);
		}
	}
	return NULL;
}

/*
** Description: Transfers buffer 2 to buffer 3, replacing all occurences of '++' with '^'
** Prerequisites: buffer 3 is allocated, buffer2 is allocated
** Updated/Returned: data is transfered into buffer3 from buffer2 with ++'s replaced.
*/
void transferBuffer2ToBuffer3() {

	pthread_mutex_lock(&buffer3Mutex);
	if (buffer3Index >= OUTPUT_LINE_LENGTH) {
		pthread_cond_wait(&buffer3DoneProcessing, &buffer3Mutex);
	}


	for (int i = 0; i < strlen(buffer2); i++) {
		if (buffer2[i] == '+' && buffer2[i + 1] == '+') {		//if we're at a ++
			buffer3[buffer3Index] = '^';
			++i;									//to get past the second '+'
			++buffer3Index;							//only increase by 1 because ^ is 1 character
		}
		else {
			buffer3[buffer3Index] = buffer2[i];
			++buffer3Index;
		}
	}
	buffer3[buffer3Index] = 0;


	pthread_cond_signal(&buffer3DoneFilling);
	pthread_mutex_unlock(&buffer3Mutex);

}