#include "lineSeparator.h"
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "buffers.h"
#include "usefulFunctions.h"
#include <stdio.h>
#include <string.h>
void* separatorLoop(void* arg) {
	while (true) {
		pthread_mutex_lock(&buffer1Mutex);
		if (!buffer1Processing) {
			pthread_cond_wait(&buffer1DoneFilling,&buffer1Mutex);
		}
		
		
		transferBuffer1ToBuffer2();


		pthread_cond_signal(&buffer1DoneProcessing);
		buffer1Processing = false;
		pthread_mutex_unlock(&buffer1Mutex);
		if (inputDone) {
			separatorDone = true;
			pthread_exit(NULL);
		}
	}
	return NULL;
}




void transferBuffer1ToBuffer2() {
	pthread_mutex_lock(&buffer2Mutex);
	if (buffer2Processing) {
		pthread_cond_wait(&buffer2DoneProcessing,&buffer2Mutex);
	}

	

	for (int i = 0; i < strlen(buffer1) + 1; i++) {
		if (buffer1[i] == '\n') {
			buffer2[i] = ' ';
		}
		else {
			buffer2[i] = buffer1[i];
		}
	}
	buffer2[strlen(buffer1)] = 0;


	buffer2Processing = true;
	pthread_cond_signal(&buffer2DoneFilling);
	pthread_mutex_unlock(&buffer2Mutex);
	

}