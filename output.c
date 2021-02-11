#include "output.h"
#include <stdbool.h>
#include <pthread.h>
#include "buffers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void* outputLoop(void* arg) {
	while (true) {
		pthread_mutex_lock(&buffer3Mutex);
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

void outputBuffer3() {
	int printIndex = 0;

	while (buffer3Index - printIndex >= OUTPUT_LINE_LENGTH) {
		
		write(1, (buffer3 + printIndex), OUTPUT_LINE_LENGTH);
		write(1, "\n", 1);
		printIndex += OUTPUT_LINE_LENGTH;

	}
	

	int charsLeft = buffer3Index - printIndex;
	for (int i = 0; i < charsLeft; i++) {
		buffer3[i] = buffer3[buffer3Index - charsLeft + i];
	}
	buffer3Index = charsLeft;

}