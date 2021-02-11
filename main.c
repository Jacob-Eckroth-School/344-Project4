#include <stdio.h>
#include "buffers.h"
#include "input.h"
#include "threads.h"
#include <stdlib.h>
int main(){
	initializeBuffers();
	initializeThreads();
	
	
	pthread_join(inputThread, NULL);	//block until input thread
	pthread_join(separatorThread, NULL);	//block until input thread
	pthread_join(plusThread, NULL);	//block until input thread
	pthread_join(outputThread, NULL);	//block until input thread
	freeBuffers();
	exit(EXIT_SUCCESS);
	return 0;
}

