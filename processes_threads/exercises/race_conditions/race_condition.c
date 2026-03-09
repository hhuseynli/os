#include <pthread.h> // POSIX Threads
#include <stdio.h>   // Standard I/O - print
#include <stdlib.h>  // Standard lib - memory
#include <unistd.h>  // UNIX Standard - sleep

#define NUMBER_OF_THREADS 10 

int var = 0;

void *increment_var(void *tid){
	// This function increments var and 'blames' a thread for a certain value
	printf("Thread %p made var = %d\n", tid, ++var);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	// The main program creates n incrementer threads and then exits.
	pthread_t threads[NUMBER_OF_THREADS];
	int status, i;

	for(i=0; i < NUMBER_OF_THREADS; i++) {

        	printf("Main here. Creating thread %d\n", i);
        	status = pthread_create(&threads[i], NULL, increment_var, (void *)i);

        	if (status != 0) {
            		printf("Oops. pthread create returned error code %d\n", status);
            		exit(-1);
        	}
	}

	for(i=0; i < NUMBER_OF_THREADS; i++) {
		/* Prevent premature exit by making sure 
		 * threads terminate before reaching the end of main. */

   		if (status = pthread_join(threads[i], NULL) != 0){
 			printf("Oops. pthread join returned error code %d\n", status);
       			exit(-1);
   	 	}
	}
	
    	exit(0);
}
