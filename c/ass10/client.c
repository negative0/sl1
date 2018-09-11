#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 

char *filename = "/tmp/fifo";

int main(int argc, char const *argv[])
{
	int fd;

	char buf1[80], buf2[80];

	while(1){

		fd = open(filename, O_RDONLY);

		read(fd, buf1, sizeof(buf1));

		printf("User 1: %s\n", buf1);
		close(fd);

		printf("\n>>>");


		fd = open(filename, O_WRONLY);

		fgets(buf2, 80, stdin);

		write(fd, buf2, strlen(buf2) + 1);
		close(fd);

	}
	
	return 0;
}