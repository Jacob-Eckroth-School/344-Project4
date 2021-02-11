#include "threads.h"
#include "output.h"
#include "plusSign.h"
#include "lineSeparator.h"
#include "input.h"
#include <stdio.h>
#include <assert.h>

pthread_t inputThread;
pthread_t separatorThread;
pthread_t plusThread;
pthread_t outputThread;


void initializeThreads() {
	int thread1Result = pthread_create(&inputThread, NULL, getInputLoop, NULL);
	int thread2Result = pthread_create(&separatorThread, NULL, separatorLoop, NULL);
	int thread3Result = pthread_create(&plusThread, NULL,plusLoop, NULL);
	int thread4Result = pthread_create(&outputThread, NULL, outputLoop, NULL);
	assert(0 == thread1Result);
	assert(0 == thread2Result);
	assert(0 == thread3Result);
	assert(0 == thread4Result);

}