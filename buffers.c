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

/*
** Description: Initializes all the buffers and related globals, and zeros them out
** Prerequisites: None
** Updated/Returned: space for buffers is allocated, variables are initialized to their starting states.
*/
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

/*
** Description: Zeros out all buffers
** Prerequisites: buffer space is allocated
** Updated/Returned: all memory in bufers is set to zero.
*/
void zeroBuffers() {
	memset(buffer1, 0, BUFFER_SIZE);
	memset(buffer2, 0, BUFFER_SIZE);
	memset(buffer3, 0, BUFFER_SIZE);
}

/*
** Description: Frees memory held by buffers
** Prerequisites: Buffers are allocated
** Updated/Returned: memory held by buffers is freed
*/
void freeBuffers() {
	if (buffer1) {
		
		free(buffer1);
	}
	if (buffer2) {
	
		free(buffer2);
	}
	if (buffer3) {
	
		free(buffer3);
	}


}


