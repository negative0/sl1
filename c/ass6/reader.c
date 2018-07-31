#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#ifndef WRITER_COUNT
#define WRITER_COUNT 10
#endif

#ifndef READER_COUNT
#define READER_COUNT 10
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

// sem_t buffer_lock;
pthread_mutex_t read_lock;
pthread_mutex_t write_lock;

int buffer[BUFFER_SIZE];
int ptr_front = 0;

void printBuffer(){
	int i;
	printf("\n");
	for (i = 0; i < BUFFER_SIZE; ++i)
	{
		if(buffer[i] != -1)
			printf("|%d|",buffer[i] );
		else
			printf("|--|" );
		/* code */
	}
	printf("\n");
}
void init_buffer(){
	int i;
	for (i = 0; i < BUFFER_SIZE; ++i){
		buffer[i] = -1;
	}
}

void *producer_function(void *arg) {
	int full,empty,s, rand_val;
	char *producer_name = (char*) arg;
	while(1){
		
		pthread_mutex_lock(&write_lock);
		pthread_mutex_lock(&read_lock);

		// Starting of critical section
		
		rand_val = rand() % BUFFER_SIZE;
		buffer[rand_val] = rand() % 100;
		printf("Put:%d\n",buffer[rand_val]);

		printf("++++++++++++++++++\n");
		printBuffer();
		printf("++++++++++++++++++\n");
		sleep(1);
		//End of critical section

		sem_post(&read_lock);
		sem_post(&write_lock);
	
	}
}

void *consumer_function(void *arg) {
	int full,empty;
	char *producer_name = (char*) arg;
	while(1){
		pthread_mutex_lock(&write_lock);
		pthread_mutex_lock(&read_lock);

		// Starting of critical section
		
		rand_val = rand() % BUFFER_SIZE;
		buffer[rand_val] = rand() % 100;
		printf("Put:%d\n",buffer[rand_val]);

		printf("++++++++++++++++++\n");
		printBuffer();
		printf("++++++++++++++++++\n");
		sleep(1);
		//End of critical section
		
		sem_post(&read_lock);
		// sem_post(&write_lock);
	
	}
}


int main(int argc, char const *argv[])
{
	pthread_t a_thread[WRITER_COUNT + READER_COUNT];
	int thread_count = 0, i, res;

	//Init Semaphores
	if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
	sem_init(&buffer_full,0,0);
	sem_init(&buffer_empty,0,BUFFER_SIZE);
	init_buffer();

	for(i=0;i<WRITER_COUNT;i++){
		char *name = malloc(3);
		sprintf(name,"%d",i);
		
		res = pthread_create(&a_thread[thread_count++], NULL, producer_function, (void*) name);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(;i<WRITER_COUNT+READER_COUNT;i++){
		char *name = malloc(3);
		sprintf(name,"%d",i);
		res = pthread_create(&a_thread[thread_count++], NULL, consumer_function, (void*) name);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<WRITER_COUNT + READER_COUNT;i++){
		res = pthread_join(a_thread[i],NULL);
		if (res != 0) {
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_destroy(&lock);
	return 0;
}