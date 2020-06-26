#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//created 10 nodes
sem_t sem0;
sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;
sem_t sem5;
sem_t sem6;
sem_t sem7;
sem_t sem8;
sem_t sem9;


pthread_t tid[10];

void* doThread0(void *arg)
{
	sleep(2);
	printf("Job0 is done.\n");
	sem_post(&sem0);
	sem_post(&sem0);
	sem_post(&sem0);
	
}

void* doThread1(void *arg)
{
	printf("Job1 is waiting Job0.\n");
	sem_wait(&sem0);
	sleep(2);
    printf("Job1 is done.\n");
    sem_post(&sem1);
}

void* doThread2(void *arg)
{
    printf("Job2 is waiting Job0.\n");
	sem_wait(&sem0);
	sleep(2);
	printf("Job2 is done.\n");
	sem_post(&sem2);

}

void* doThread3(void *arg)
{
	printf("Job3 is waiting Job0.\n");
	sem_wait(&sem0);
	sleep(2);
    printf("Job3 is done.\n");
	sem_post(&sem3);
	
}

void* doThread4(void *arg)
{
	printf("Job4 is waiting Job1 and Job2.\n");
	sem_wait(&sem1);
	sem_wait(&sem2);
	sleep(2);
	printf("Job4 is done.\n");
	sem_post(&sem4);
	sem_post(&sem4);
}

void* doThread5(void *arg)
{
    printf("Job5 is waiting Job3.\n");
	sem_wait(&sem3);
	sleep(2);
    printf("Job5 is done.\n");
    sem_post(&sem5);
	sem_post(&sem5);

}

void* doThread6(void *arg)
{
	printf("Job6 is waiting Job4.\n");
	sem_wait(&sem4);
	sleep(2);
    printf("Job6 is done.\n");
    sem_post(&sem6);
}

void* doThread7(void *arg)
{
	printf("Job7 is waiting Job4 and Job5.\n");
	sem_wait(&sem4);
	sem_wait(&sem5);
	sleep(2);
    printf("Job7 is done.\n");
    sem_post(&sem7);
}

void* doThread8(void *arg)
{
	printf("Job8 is waiting Job5.\n");
	sem_wait(&sem5);
	sleep(2);
    printf("Job8 is done.\n");
	sem_post(&sem8);
	
}

void* doThread9(void *arg)
{
    printf("Job9 is waiting Job6, Job7 and Job8.\n");
    sem_wait(&sem6);
	sem_wait(&sem7);
	sem_wait(&sem8);
	sleep(2);
    printf("Job9 is done.\n");
	
}

int main(int argc, char *argv[]) {
	
	pthread_create(&(tid[0]), NULL, &doThread0, NULL);
	pthread_create(&(tid[1]), NULL, &doThread1, NULL);
	pthread_create(&(tid[2]), NULL, &doThread2, NULL);
	pthread_create(&(tid[3]), NULL, &doThread3, NULL);
	pthread_create(&(tid[4]), NULL, &doThread4, NULL);
	pthread_create(&(tid[5]), NULL, &doThread5, NULL);
	pthread_create(&(tid[6]), NULL, &doThread6, NULL);
	pthread_create(&(tid[7]), NULL, &doThread7, NULL);
	pthread_create(&(tid[8]), NULL, &doThread8, NULL);
	pthread_create(&(tid[9]), NULL, &doThread9, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	pthread_join(tid[4], NULL);
	pthread_join(tid[5], NULL);
	pthread_join(tid[6], NULL);
	pthread_join(tid[7], NULL);
	pthread_join(tid[8], NULL);
	pthread_join(tid[9], NULL);
}