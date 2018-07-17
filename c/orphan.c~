/* C program for Merge Sort */
#include<stdlib.h>
#include<stdio.h>
#define MAX 10

/* Driver program to test above functions */
int main()
{
    int status;
   
    status = fork();
    if(status != 0){
	    printf("In Parent: PID,PPID: %d, %d\n",getpid(),getppid());
	     sleep(10);
	    //printf("\nSorted array is \n");

	    printf("Parent Exiting\n");
	    //sleep(10);
	    wait();
	    //system("wait");
	    printf("Parent Wait Complete");
	    //exit(-1);
	
    }else{
    	printf("Child Executing!\n");
    	printf("In child: PID, PPID:%d, %d\n",getpid(),getppid());
    	printf("Stopping child\n");
    	exit(-1);
    	//while(1){}
   
	
	
    }
    
    return 0;
}

