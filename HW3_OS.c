#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#define NO_OF_THREADS 10

struct Singleton {
    char *Data;
};


struct Singleton *singletonObjectPointer;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int addresses[NO_OF_THREADS];
sem_t sem;

void *runner(void *params); /* the thread */
struct Singleton *getInstance();

int main()
{
	int i;
	sem_init(&sem,0,1);
	pthread_t threadIds[NO_OF_THREADS];


	for (i=0; i < NO_OF_THREADS; i++){
		pthread_create(&threadIds[i], NULL, &runner, (void *)(i));
	}

	/* Wait until all threads are done */
	for (i=0; i < NO_OF_THREADS; i++){
		pthread_join(threadIds[i], NULL);

	}

	/* Control addresses. All of them should be same */
	int prevAddr=addresses[0];
	for (i=1; i < NO_OF_THREADS; i++){
		if(addresses[i]!=prevAddr){
			printf("Object is created more than once\n");
			return -1;
		}
		prevAddr=addresses[i];
	}
	for (i=0; i < NO_OF_THREADS; i++){
		printf("Singleton Addresses for each thread %x\n",addresses[i]);
	}
	printf("Successful\n");
	return 1;
}

void *runner(void *params)
{

	int i = (int)params;
	printf("Thread %d\n",i);
    // Blocking the deadlock
    pthread_mutex_lock(&mutex);
	struct Singleton *s = getInstance(i);
    addresses[i]=s;

    //To enter to other threads
    pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}

//Fill this method
struct Singleton *getInstance(){    
    int val;
    //To check semaphore that's value is read.
    sem_getvalue(&sem, &val);
    //If value is 0, there is struct type previously
    //Array checked and new object showing the same block
    if (val == 0) {
        int j=0;
        while(j<NO_OF_THREADS){
             if (addresses[j] != 0) {
          singletonObjectPointer = (struct Singleton *)malloc(sizeof(struct Singleton));
          singletonObjectPointer = addresses[j];
          return singletonObjectPointer;
        }
        j+=1;
        }
    }
    //Since the semaphore is open if the value is not 0, the semaphore is closed and the first object is created.
    sem_wait(&sem);
		singletonObjectPointer = (struct Singleton *)malloc(sizeof(struct Singleton));
		printf("---Address of singletonObjectPointer is %x\n",singletonObjectPointer);
		singletonObjectPointer->Data="This is object data";

	return singletonObjectPointer;
}
