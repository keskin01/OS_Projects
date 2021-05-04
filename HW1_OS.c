#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>

#define HEIGHT 7
#define MARBLE 1000000


int slots[HEIGHT+1];	//result array
pthread_mutex_t locks[HEIGHT+1];	//locks for results

pthread_t threads[100];	//the arrays for the threads to wait

void *runner(void *params); /* the thread */

void main(){
	int i;
	i=0;
	while(i<(HEIGHT+1))
	{
	    pthread_mutex_init(&locks[i], NULL);
	    i+=1;
	}

	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	// set the detach so threads are released as soon as they finish
	i=0;
	while(i<MARBLE){
	    pthread_create(&threads[i%100], &attr, runner, NULL);
	    i++;
	}
	while(i<100){
	    pthread_join(threads[i],NULL);
	    i++;
	}
	
	pthread_attr_destroy(&attr);
	
	int sum=0;
	for(i=0; i<HEIGHT+1; i++){
		sum+=slots[i];
		printf("%3d %d\n", i, slots[i]);
	}
	printf("sum: %d\n", sum);
}

void *runner(void *params) 
{
	srand((int)pthread_self());	//create seed depending on thread itself
	
	int slot=0;
	int random=rand()%(int)(pow(2,HEIGHT));	//create a sequence of L and R. 0=L, 1=R
	int i;
	for(i=0;i<HEIGHT;i++){	//check R's and move the slot
		slot += (random >> i)&1; 
	}
	
	pthread_mutex_lock(&locks[slot]);
	slots[slot]=slots[slot]+1;
	pthread_mutex_unlock(&locks[slot]);
}
