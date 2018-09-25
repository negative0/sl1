#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd[2];

	char buf1[50] = "Hello World";
	char buf2[50];

	fd[0] = open("foobar.txt", O_CREAT | O_RDWR);
	// fd[1] = open("foobar.txt", O_RDWR);

	write(fd[0], buf1, strlen(buf1));

	close(fd[0]);
	return 0;
}