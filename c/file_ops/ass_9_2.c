#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int createFile(){
	int fd = open("myfile.txt", O_CREAT | O_RDWR, S_IRWXU);

	if(fd == -1){
		perror("Error Creating File\n");
	}
	return fd;
}

int readFromFile(int fd, char string[50]){
	int readSize;
	if(fd<0){
		fd = createFile();
	}

	readSize = read(fd, string, sizeof(string));

	// string[readSize] = '\0';

	return readSize;
}

int writeToFile(int fd, char string[50]){
	int writeSize;

	if(fd<0){
		fd = createFile();
	}

	writeSize = write(fd, string, sizeof(string));

	return writeSize;
}



int main(int argc, char const *argv[])
{
	int fd = -1, choice;


	char buf2[50];
	while(1){
		printf("\n1.Create New File\n2.Read From existing\n3.Write to existing file\n4.Exit\n");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				fd = createFile();
			break;

			case 2:
				readFromFile(fd, buf2);
				writeToFile(1, buf2);
			break;

			case 3:
				read(0, buf2, sizeof(buf2));
				
				write(1, buf2, sizeof(buf2));
				writeToFile(fd, buf2);
				printf("Write Complete\n");
			break;

			case 4:
				return 1;
			break;
		}
	}

	return 0;
}