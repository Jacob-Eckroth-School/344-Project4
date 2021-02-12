#include "input.h"
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include "buffers.h"
#include <string.h>
#include "usefulFunctions.h"
#include <assert.h>



/*
** Description: Gets input from user until user enters a line with only STOP
** Prerequisites: buffer1 is allocated
** Updated/Returned: buffer1 keeps being updated with data inputted by user until user says STOP
*/
void* getInputLoop(void* arg) {
	assert(buffer1);
	size_t stringSize = 0;
	while (true) {
		
		pthread_mutex_lock(&buffer1Mutex);
		
		//if line separator thread is still processing buffer1
		if (buffer1Processing) {
			pthread_cond_wait(&buffer1DoneProcessing, &buffer1Mutex);
		}
		getline(&buffer1, &stringSize, stdin);
		
		//line separator thread will set this back to false when it's done with the content
		buffer1Processing = true;


		if (strcmp(buffer1, "STOP\n") == 0) {
			
			inputDone = true;

			memset(buffer1, 0, BUFFER_SIZE);	//if it's stop we want to get rid of it so we don't print it at all
			pthread_cond_signal(&buffer1DoneFilling);
			pthread_mutex_unlock(&buffer1Mutex);
			pthread_exit(NULL);
		}
		

		pthread_cond_signal(&buffer1DoneFilling);
		pthread_mutex_unlock(&buffer1Mutex);

		

	}
	//this return will never be reached... in theory
	return NULL;
}