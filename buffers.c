#include "buffers.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
char* buffer1 = NULL;
char* buffer2 = NULL;
char* buffer3 = NULL;
pthread_mutex_t buffer1Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t buffer2Mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t buffer3Mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t buffer1DoneProcessing = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer1DoneFilling = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer2DoneProcessing = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer2DoneFilling = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer3DoneProcessing = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer3DoneFilling = PTHREAD_COND_INITIALIZER;

 bool buffer1Processing;
 bool buffer2Processing;
 bool buffer3Processing;
 int buffer3Index;
 bool inputDone;
bool plusDone;
bool separatorDone;
void initializeBuffers() {
	buffer1 = malloc(sizeof(char) * BUFFER_SIZE);
	buffer2 = malloc(sizeof(char) * BUFFER_SIZE);
	buffer3 = malloc(sizeof(char) * BUFFER_SIZE);
	buffer3Index = 0;
	buffer1Processing = buffer2Processing = buffer3Processing = false;
	inputDone = false;
	plusDone = false;
	separatorDone = false;
	zeroBuffers();
}

void zeroBuffers() {
	memset(buffer1, 0, BUFFER_SIZE);
	memset(buffer2, 0, BUFFER_SIZE);
	memset(buffer3, 0, BUFFER_SIZE);
}

void freeBuffers() {
	free(buffer1);
	free(buffer2);
	free(buffer3);

}


