#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	pid_t pid;
	int pipefd[2]; //this is to be passed in the pipe system call
	char buffer[15];
	pipe(pipefd); 
	pid= fork();
	
	if(pid>0)
	{
		fflush(stdin);
		printf("\nAn parent: will write helloworld ");
		write(pipefd[1],"HELLO WORLD\n",12);
		
	}
	if(pid==0)
	{
		sleep(1);
		fflush(stdin);
		fprintf(stderr,"\nAn Child will read hello world:");
		read(pipefd[0],buffer,sizeof(buffer));
		write(1,buffer,sizeof(buffer)); //Display to output screen
		
	}
	return 0;
}
