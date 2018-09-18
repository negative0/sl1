#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define RAND_SLEEP_MAX 5
#define NUM_PHILOSPHERS 100

#define THINKING 1
#define EATING 2
#define HUNGRY 3

int states[NUM_PHILOSPHERS];
sem_t sem_states[NUM_PHILOSPHERS];
int num;

pthread_mutex_t temp_lock;
pthread_mutex_t print_lock;

void randSleep(){
	sleep(rand()%RAND_SLEEP_MAX);
}

void showStatus(){
	pthread_mutex_lock(&temp_lock);
	pthread_mutex_lock(&print_lock);
	int i;
	char c;
	for(i=0;i<num;i++){
		printf("|%d|",i);
	}
	printf("\n---------------------------------\n");
	for(i=0;i<num;i++){
		
		if(states[i] == THINKING){
			c = 'T';
		}else if(states[i] == EATING){
			c = 'E';
		}else if(states[i] == HUNGRY){
			c = 'H';
		}else{
			c = 'U';
		}
		printf("|%c|",c );
	}
	printf("\n---------------------------------\n");

	pthread_mutex_unlock(&print_lock);
	pthread_mutex_unlock(&temp_lock);
}

void eat(int i){
	printf("Philosopher [%d] is eating\n",i );
	//states[i] = EATING;
	showStatus();
	randSleep();
}

void think(int i){
	printf("Philosopher [%d] is thinking\n",i );
	states[i] = THINKING;
	showStatus();
	randSleep();
}

int getLeft(int i){
	return (i - 1 + NUM_PHILOSPHERS) % NUM_PHILOSPHERS;
}

int getRight(int i){
	return (i + 1)%NUM_PHILOSPHERS;
}

void test(int i){
	if(states[i] == HUNGRY && states[getLeft(i)] != EATING && states[getRight(i)] != EATING){
		states[i] = EATING;
		sem_post(&sem_states[i]);
	}
}

int is_hungry(){
	return rand()%2;
}

void takefork(int i){
	pthread_mutex_lock(&temp_lock);
	test(i);
	pthread_mutex_unlock(&temp_lock);
	sem_post(&sem_states[i]);
}
void putfork(int i){
	// printf("%s\n", );
	pthread_mutex_lock(&temp_lock);
	//states[i] = THINKING;
	test(getLeft(i));
	test(getRight(i));
	pthread_mutex_unlock(&temp_lock);
}

void* philosopher(void* arg){
	int* i = (int *) arg;
	while(1){
		think(*i);
		if(is_hungry() == 1){
			printf("Philosopher [%d] is hungry\n", *i );
			states[*i] = HUNGRY;
			takefork(*i);
			eat(*i);
			putfork(*i);
		}
	}
}

void main(){
	int i;
	pthread_t philosophers_t[NUM_PHILOSPHERS];
	if(pthread_mutex_init(&temp_lock, NULL) != 0){
		printf("Mutex init failed\n");
	}
	printf("Enter no of philosophers:\n");
	scanf("%d", &num);
	for(i = 0; i < num; i++){
		int *a = malloc(sizeof(int));
		*a = i;
		sem_init(&sem_states[i], 0, 0);
		pthread_create(&philosophers_t[i], NULL, philosopher, (void *) a);
	}

	for(i=0;i<NUM_PHILOSPHERS;i++){
		pthread_join(philosophers_t[i], NULL);
	}
}