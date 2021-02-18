/*
Name: Jacob Eckroth
Date: 2/22/2021
Project Name: Assignment 4: Multi-threaded Producer Consumer Pipeline
Description: This program is a multi-threaded process. It takes input from stdin, until it receives a line that is just
**			"STOP\n". It removes all line separators and replaces them with spaces, replaces all occurences of ++ with '^'
**			and then outputs lines in 80 character chunks to stdout. If the last line after STOP has less than 80 characters
**			Then it is not sent to stdout.
*/


#include <stdio.h>
#include "buffers.h"
#include "input.h"
#include "threads.h"
#include <stdlib.h>
#include <pthread.h>

/*
** Description: This is the main function.... it runs the program... that's it
** Prerequisites: are you dumb
** Updated/Returned: this is the main function of a program. Everything is very clearly well named. You got this I believe in you
*/
int main(){
	initializeBuffers();
	initializeThreads();
	
	pthread_join(inputThread, NULL);	//block until input thread
	pthread_join(separatorThread, NULL);	//block until separator thread
	pthread_join(plusThread, NULL);	//block until plus thread
	pthread_join(outputThread, NULL);	//block until output thread
	freeBuffers();

	return 0;
}

