#ifndef THREADS
#define THREADS
#include <pthread.h>

extern pthread_t inputThread;
extern pthread_t separatorThread;
extern pthread_t plusThread;
extern pthread_t outputThread;


void initializeThreads();

#endif