#ifndef BUFFER
#define BUFFER

#include <stdbool.h>
#include <pthread.h>
#define BUFFER_SIZE 1001
#define OUTPUT_LINE_LENGTH 80

extern char* buffer1;
extern char* buffer2;
extern char* buffer3;

extern pthread_mutex_t buffer1Mutex;
extern pthread_mutex_t buffer2Mutex;
extern pthread_mutex_t buffer3Mutex;

extern pthread_cond_t buffer1DoneProcessing;
extern pthread_cond_t buffer1DoneFilling;
extern pthread_cond_t buffer2DoneProcessing;
extern pthread_cond_t buffer2DoneFilling;
extern pthread_cond_t buffer3DoneProcessing;
extern pthread_cond_t buffer3DoneFilling;


extern int buffer3Index;

extern bool buffer1Processing;
extern bool buffer2Processing;
extern bool buffer3Processing;
extern bool inputDone;
extern bool plusDone;
extern bool separatorDone;



void zeroBuffers();

void initializeBuffers();

void freeBuffers();

#endif