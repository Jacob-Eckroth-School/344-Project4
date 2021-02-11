#include "plusSign.h"
#include <stdlib.h>
#include <stdbool.h>
#include "buffers.h"
#include <pthread.h>
#include <string.h>
#include "usefulFunctions.h"
#include <stdio.h>
void* plusLoop(void* arg) {
	while (true) {
		pthread_mutex_lock(&buffer2Mutex);
		if (!buffer2Processing) {
			 
			pthread_cond_wait(&buffer2DoneFilling, &buffer2Mutex);
		}

		transferBuffer2ToBuffer3();

		pthread_cond_signal(&buffer2DoneProcessing);
		buffer2Processing = false;
		pthread_mutex_unlock(&buffer2Mutex);
		if (separatorDone) {
			plusDone = true;
			pthread_exit(NULL);
		}
	}


	return NULL;
}

void transferBuffer2ToBuffer3() {

	pthread_mutex_lock(&buffer3Mutex);
	if (buffer3Index>=OUTPUT_LINE_LENGTH) {
		pthread_cond_wait(&buffer3DoneProcessing, &buffer3Mutex);
	}


	for (int i = 0; i < strlen(buffer2); i++) {
		if (buffer2[i] == '+' && buffer2[i+1] == '+') {
			buffer3[buffer3Index] = '^';
			++i;
			++buffer3Index;
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