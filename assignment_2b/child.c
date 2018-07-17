#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

int main(int argc,char* argv[])
{
	int n=argc;
	
	printf("In child : \n");
	printf("array : \n");
	for (int i = 0; i < n; ++i)
	{
		/* code */
		printf("%s ",argv[i]);
	}
	
	

	return 0;
}