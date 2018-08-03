#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t buf_lock;
pthread_mutex_t read_lock;
pthread_mutex_t print_lock;

int writer_count, reader_count, buffer_size;
int read_count;
int write_count;

int *buffer;

int readers_c = 0;

void printBuffer(int op, int rand_val){
	int i;
	pthread_mutex_lock(&print_lock);
	if(op==0){
		printf("Writing @ %d:(%d)\n",rand_val,buffer[rand_val]);
	}else{
		printf("Reading @ %d:(%d)\n",rand_val,buffer[rand_val]);
	}
	printf("\n++++++++++++++++++\n");

	for (i = 1; i <= buffer_size; ++i)
	{
		if(buffer[i-1] != -1)
			printf("|%d|",buffer[i] );
		else
			printf("|--|" );
		if(i%10==0)printf("\n");
		/* code */
	}
	if(op != 0)
		printf("\nReaders:%d\tTReads:%d\tTWrites:%d\n", readers_c,read_count, write_count);
	else
		printf("\nReaders:0\tTReads:%d\tTWrites:%d\n",read_count, write_count);
	printf("\n++++++++++++++++++\n");
	pthread_mutex_unlock(&print_lock);
}
void init_buffer(){
	int i;
	buffer = malloc(sizeof(int) * buffer_size);
	for (i = 0; i < buffer_size; ++i){
		buffer[i] = -1;
	}
}

void *producer_function(void *arg) {
	int full,empty,s, rand_val;
	char *producer_name = (char*) arg;
	while(1){
		sleep(rand() % 3);
		
		pthread_mutex_lock(&buf_lock);

		// Starting of critical section
		write_count++;
		rand_val = rand() % buffer_size;
		buffer[rand_val] = rand() % 100;

		sleep(1);
		printBuffer(0, rand_val);
		
		
		//End of critical section
		pthread_mutex_unlock(&buf_lock);

	
	}
}

void *consumer_function(void *arg) {
	int full,empty, rand_val;
	char *producer_name = (char*) arg;
	while(1){
		sleep(rand() % 4);
		pthread_mutex_lock(&read_lock);
		readers_c += 1;
		if(readers_c == 1){
			pthread_mutex_lock(&buf_lock);
		}
		pthread_mutex_unlock(&read_lock);

		// Starting of critical section
		read_count++;
		rand_val = rand() % buffer_size;
		sleep(1);
		printBuffer(1, rand_val);
		
		//End of critical section
		
		pthread_mutex_lock(&read_lock);
		readers_c -= 1;
		if(readers_c == 0){
			pthread_mutex_unlock(&buf_lock);
		}
		pthread_mutex_unlock(&read_lock);
	
	}
}
int init_semaphores(){
	//Init Semaphores
	if (pthread_mutex_init(&buf_lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
    //Init Semaphores
	if (pthread_mutex_init(&read_lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
    if (pthread_mutex_init(&print_lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
}


void initMain(){
	printf("Enter the reader count and writer_count:\n");
	scanf("%d%d",&reader_count,&writer_count);
	printf("Enter the buffer size:\n");
	scanf("%d",&buffer_size);
}


int main(int argc, char const *argv[])
{
	int thread_count = 0, i, res;
	initMain();
	pthread_t a_thread[reader_count + writer_count];
	if(init_semaphores() == 1){
		return 1;
	}

	init_buffer();

	for(i=0;i<writer_count;i++){
		char *name = malloc(3);
		sprintf(name,"%d",i);
		
		res = pthread_create(&a_thread[thread_count++], NULL, producer_function, (void*) name);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(;i<reader_count + writer_count;i++){
		char *name = malloc(3);
		sprintf(name,"%d",i);
		res = pthread_create(&a_thread[thread_count++], NULL, consumer_function, (void*) name);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
	}
	for(i=0;i<reader_count + writer_count;i++){
		res = pthread_join(a_thread[i],NULL);
		if (res != 0) {
			perror("Thread join failed");
			exit(EXIT_FAILURE);
		}
	}
	pthread_mutex_destroy(&buf_lock);
	pthread_mutex_destroy(&read_lock);

	return 0;
}