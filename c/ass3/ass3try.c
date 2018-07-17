#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct val
{
	char *name;
	int th_no;	
}vala;
void *thread_function(void *arg);
void *thread_function1(void *arg);

char message[] = "Hello World";
int main() {
	int res, j;
	pthread_t a_thread;
	void *thread_result;
	
	for(j=0;j<5;j++){
		vala *vl = malloc(sizeof(vala));
		vl->th_no = j;
		res = pthread_create(&a_thread, NULL, thread_function1, (void *)vl);
		if (res != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
		//res = pthread_join(a_thread, &thread_result);
		//if (res != 0) {
		//	perror("Thread join failed");
		//	exit(EXIT_FAILURE);
		//}
	}
	sleep(20);
	printf("%s\n", "Out of sleep");
	//res = pthread_join(a_thread, &thread_result);
	if (res != 0) {
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	// printf("Thread joined, it returned %s\n", (char *)thread_result);
	// printf("Message is now %s\n", message);
	exit(EXIT_SUCCESS);
}
void *thread_function(void *arg) {
	printf("thread_function is running. Argument was %s\n", (char *)arg);
	sleep(3);
	strcpy(message, "Bye!");
	pthread_exit("Thank you for the CPU time");
}
void *thread_function1(void *arg) {
	int i = 0;
	for(i=0;i<30;i++){
		printf("Thread %d:%d\n",((vala *)arg)->th_no, i);
		sleep(1);
	}
}