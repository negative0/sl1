#include<stdio.h>

int main(){
	int status;
	
	status = fork();
	
	if(status != 0){
		printf("Parent Executing!\n");

		//sleep(100);
		wait();
		printf("Stopping Parent!\n");
		
	}else{
		printf("Child Executing!\n");
		sleep(10);
		printf("Stopping child\n");
	}


}
