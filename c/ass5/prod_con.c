#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
sem_t e;
sem_t f;
sem_t s;
int buffer[10]={-1};
int count=0;

void* producer (void *m)
{
	
	while(1)
	{
		int item,i;
		// printf("In Prodcer\n");

	sem_wait(&e);
	sem_wait(&s);
		// printf("In Producer Critical Section\n");

	
	
		item=rand()%100;
		buffer[count]=item;
		count++;
		printf("\n");
		for(i=0;i<count;i++)
		{
			if(buffer[i]!=-1)
				printf("%d\t",buffer[i]);
			else
				printf("-\t");
		}
		printf("\n");

	
	
	
	sleep(1);
	sem_post(&s);
	sem_post(&f);
	}
}

void* consumer (void *m)
{

	
	
	while(1)
	{
		// printf("In Consumer\n");
		int item,i;
	sem_wait(&f);
	sem_wait(&s);
	// printf("In Consumer Critical Section\n");
	
		item=buffer[count];
		count--;
		printf("\n");
		for(i=0;i<count;i++)
		{
			if(buffer[i]!=-1)
				printf("%d\t",buffer[i]);
			else
				printf("-\t");
		}
		printf("\n");
	
	sleep(1);
	sem_post(&s);
	sem_post(&e);
	}	
	
}
int main()
{	

	pthread_t prod[10],cons[10];
	int no_prod,no_cons,i;
	printf("enter no of producers and consumers :\n");
	scanf("%d %d",&no_prod,&no_cons);
	
	sem_init(&s,0,1);
	sem_init(&e,0,10);
	sem_init(&f,0,0);

	for(i=0;i<no_prod;i++)
		pthread_create(&prod[i],NULL,producer,&i);

	for(i=0;i<no_cons;i++)
		pthread_create(&cons[i],NULL,consumer,&i);
	
	for(i=0;i<no_prod;i++)
		pthread_join(prod[i],NULL);

	for(i=0;i<no_prod;i++)
		pthread_join(cons[i],NULL);

	sem_destroy(&e);
	sem_destroy(&f);
}


