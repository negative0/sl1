#include<unistd.h>
#include <stdio.h>
#include <wait.h>


int main(int argc, char const *argv[])
{
	int fd1[2], fd2[2];
	int a, b;
	int status;
	char buffer1[100], buffer2[100];

	pipe(fd1);
	pipe(fd2);
	status = fork();
	if(status != 0){
		//In Parent
		//sleep(1);
		fflush(stdin);
	
		write(fd1[1], "Hello from Parent!\n", 20);

		//sleep(5);
		wait(&status);
		read(fd2[0],buffer1, sizeof(buffer1));
		printf("Parent:%s\t\n", buffer1);
	}else{
		
		sleep(1);
			fflush(stdin);
		//In Child
		
		read(fd1[0], buffer2, sizeof(buffer2));
		printf("Child:%s\t\n", buffer2);
		

		write(fd2[1], "Hello from  Child!\n", 20);
	

	}


	return 0;
}