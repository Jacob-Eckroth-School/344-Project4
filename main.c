/*
Name: Jacob Eckroth
Date: 2/22/2021
Project Name: Assignment 4: Multi-threaded Producer Consumer Pipeline
Description: This program runs a shell. There are 3 written in commands. CD, Status, and Exit.
**			All other commands are handled by the exec family of functions. Supports redirecting input/output once.
**			Supports background execution of commands.
**			General Syntax: command [arg1 arg2 ...] [< input_file] [> output_file] [&]
**			Comments can be made on lines starting with '#'
*/


#include <stdio.h>
#include "buffers.h"
#include "input.h"
#include "threads.h"
#include <stdlib.h>


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

