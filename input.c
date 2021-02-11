#include "input.h"
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include "buffers.h"
#include <string.h>
#include "usefulFunctions.h"
void* getInputLoop(void* arg) {
	size_t stringSize = 0;
	while (true) {
		
		pthread_mutex_lock(&buffer1Mutex);
		
		if (buffer1Processing) {
			pthread_cond_wait(&buffer1DoneProcessing, &buffer1Mutex);
		}
		getline(&buffer1, &stringSize, stdin);
		
		buffer1Processing = true;

		if (strcmp(buffer1, "STOP\n") == 0) {
			
			inputDone = true;
			pthread_cond_signal(&buffer1DoneFilling);
			pthread_mutex_unlock(&buffer1Mutex);
			pthread_exit(NULL);
		}
		

		pthread_cond_signal(&buffer1DoneFilling);
		pthread_mutex_unlock(&buffer1Mutex);

		

	}
	return NULL;
}