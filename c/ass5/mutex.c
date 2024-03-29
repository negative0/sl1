#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#ifndef PRODUCER_COUNT
#define PRODUCER_COUNT 10
#endif

#ifndef CONSUMER_COUNT
#define CONSUMER_COUNT 10
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

// sem_t buffer_lock;
pthread_mutex_t lock;
sem_t buffer_empty;
sem_t buffer_full;

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
	int full,empty,s;
	char *producer_name = (char*) arg;
	while(1){
		printf("(Producer:%s):I've decremented Empty \n",producer_name);
		sem_wait(&buffer_empty);
		pthread_mutex_lock(&lock);
		// Starting of critical section
		printf("(Producer:%s):I've entered critical section\n",producer_name);
		
		
		printf("++++++++++\nProducer:%s\n",producer_name);

		buffer[ptr_front] = rand() % 100;
		ptr_front = ptr_front+1 % BUFFER_SIZE;
		printf("Put:%d\n",buffer[ptr_front]);
		sem_getvalue(&buffer_full, &full);
		sem_getvalue(&buffer_empty, &empty);

		// sem_getvalue(&buffer_lock, &s);

		printf("Full:%d\tEmpty:%d\n++++++++++++",full,empty);
		printBuffer();
		printf("++++++++++++++++++\n");
		sleep(1);
		//End of critical section
		pthread_mutex_unlock(&lock);
		sem_post(&buffer_full);
	}
}

void *consumer_function(void *arg) {
	int full,empty;
	while(1){
		char *producer_name = (char*) arg;
		printf("(Consumer:%s):I've decremented Full\n",producer_name);
		sem_wait(&buffer_full);
		pthread_mutex_lock(&lock);
		// Starting of critical section
		printf("(Consumer:%s):I've entered critical section\n",producer_name);
		printf("++++++++++\nConsumer:%s\n",producer_name);
		printf("Fetch:%d\n",buffer[ptr_front] );
		buffer[ptr_front] = -1;
		ptr_front = ptr_front-1 % BUFFER_SIZE;

		
		
		sem_getvalue(&buffer_full, &full);
		sem_getvalue(&buffer_empty, &empty);
		// sem_getvalue(&buffer_lock, &s);

		printf("Full:%d\tEmpty:%d\n++++++++++++",full,empty);
		printBuffer();
		printf("++++++++++++++++++\n");
		sleep(1);

		//End of critical section
		pthread_mutex_unlock(&lock);
		sem_post(&buffer_empty);
	}
}


int main(int argc, char const *argv[])
{
	pthread_t a_thread[PRODUCER_COUNT + CONSUMER_COUNT];
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

	for(i=0;i<PRODUCER_COUNT;i++){
		char *name = malloc(3);
		sprintf(name,"%d",i);
		
		res = pthread_create(&a_thread[thread_count++], NULL, producer_function, (void*) name);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(;i<PRODUCER_COUNT+CONSUMER_COUNT;i++){
		char *name = malloc(3);
		sprintf(name,"%d",i);
		res = pthread_create(&a_thread[thread_count++], NULL, consumer_function, (void*) name);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<PRODUCER_COUNT + CONSUMER_COUNT;i++){
		res = pthread_join(a_thread[i],NULL);
		if (res != 0) {
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_destroy(&lock);
	return 0;
}