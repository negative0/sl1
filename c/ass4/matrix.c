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
	int m[MAX][MAX];
}Matrix;

Matrix gl_m1, gl_m2, gl_res;

typedef struct Operation
{
	int r,c;
	int cr,cc;
}Operation;

void acceptMatrix(Matrix *m1, int r, int c){
	int i,j;
	
	for(i=0;i<m1->r;i++){
		for(j=0;j<m1->c;j++){
			printf("Enter Value for:(%d,%d):\n",i+1,j+1 );
			scanf("%d", &m1->m[i][j]);
		}
	}
}

void displayMatrix(Matrix m1){
	int i,j;
	for(i=0;i<m1.r;i++){
		printf("\n----------\n");
		for(j=0;j<m1.c;j++){
			printf("|%d|",m1.m[i][j]);
		}
	}
}

void *thread_function(void *arg) {
	Operation *op = (Operation *) arg;
	int k;
	int out = 0;
	int i = op->cr;
	int j = op->cc;
	for(k=0;k<op->c;k++){
		out += gl_m1.m[i][k]*gl_m2.m[k][j];
	}
	gl_res.m[i][j] = out;
	printf("Thread(%d,%d):%d\n",i,j,out);
}

int main(int argc, char const *argv[])
{
	int i,j,res;
	pthread_t a_thread[MAX][MAX];
	gl_m1.r = MAX;
	gl_m1.c = MAX;
	gl_m2.r = MAX;
	gl_m2.c = MAX;
	
	acceptMatrix(&gl_m1);
	acceptMatrix(&gl_m2);
	gl_res.r = MAX;
	gl_res.c = MAX;

	displayMatrix(gl_m1);
	displayMatrix(gl_m2);
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
			res = pthread_join(a_thread[i][j],NULL);
			if (res != 0) {
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}	
		}
	}

	displayMatrix(gl_res);
	

	return 0;
}