#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#ifndef MAX
#define MAX 3
#endif

typedef struct Matrix
{
	int r,c;
	int *m;
}Matrix;

Matrix *gl_m1, *gl_m2, *gl_res;

typedef struct Operation
{
	int r,c;
	int cr,cc;
}Operation;

void displayMatrix(Matrix *m1){
	int i,j;
	printf("\n-+-+-+-+-+-+\n");
	for(i=0;i<m1->r;i++){
		printf("\n----------\n");
		for(j=0;j<m1->c;j++){
			printf("|%d|",getElement(m1, i,j));
		}
	}
	printf("\n-+-+-+-+-+-+\n");
}

int getElement(Matrix *m1, int i, int j){
	// printf("%d\n", *((m1->m+i)+j));
	return *((m1->m + (i*m1->c)+j));
}

void putElement(Matrix *m1, int i, int j, int value){
	*(((m1->m)+ (i*(m1->c)))+j) = value;
	
}

Matrix *initMatrix(int r,int c){
	Matrix *m1;
	printf("Here\n");
	m1 = malloc(sizeof(Matrix));
	m1->m = malloc(sizeof(int) * r * c);
	m1->r = r;
	m1->c = c;
	printf("Init complete\n");
	return m1;
}

Matrix *acceptMatrix(int r, int c){
	int i,j;
	int temp;
	Matrix *m1;

	m1 = initMatrix(r,c);

	for(i=0;i<m1->r;i++){
		for(j=0;j<m1->c;j++){
			printf("Enter Value for:(%d,%d):\n",i+1,j+1 );
			scanf("%d", &temp);
			putElement(m1,i,j,temp);
		}
	}
	return m1;
}





void *thread_function(void *arg) {
	Operation *op = (Operation *) arg;
	int k;
	int *out = malloc(sizeof(int));
	int i = op->cr;
	int j = op->cc;
	for(k=0;k<op->c;k++){
		*out += getElement(gl_m1,i,k) * getElement(gl_m2,k,j);
	}
	

	printf("Thread(%d,%d):%d\n",i,j,*out);
	pthread_exit((void *) out);
}

int main(int argc, char const *argv[])
{
	int i,j,res;
	int r1,c1,r2,c2;
	pthread_t a_thread[MAX][MAX];
	void *my_result;

	printf("Enter the number of rows and columns:\n");
	scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
	// a_thread = malloc(sizeof(pthread_t) * r1 * c1);
	gl_m1 = acceptMatrix(r1,c1);
	displayMatrix(gl_m1);
	gl_m2 = acceptMatrix(r2,c2);
	displayMatrix(gl_m2);
	gl_res = initMatrix(r1,c2);

	//INIT RESULT MATRIX

	Operation *op;
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++){
			op = malloc(sizeof(Operation));
			op->r = MAX;
			op->c = MAX;

			op->cr = i;
			op->cc = j;
			res = pthread_create(&a_thread[i][j], NULL, thread_function, (void *)op);
			if (res != 0) {
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
		}
	}

	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++){
			res = pthread_join(a_thread[i][j],&my_result);
			putElement(gl_res, i,j, *((int *)my_result));
			if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}	
		}
	}

	displayMatrix(gl_res);
	

	return 0;
}