#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main()
{
	int n;
	printf("Enter n : \n");
	scanf("%d",&n);
	int a[n];
	printf("Enter array : \n");
	for (int i = 0; i < n; ++i)
	{
		/* code */
		scanf("%d",&a[i]);
	}
	qsort(a, n, sizeof(int), cmpfunc);
	char* arg[100]={NULL};
	char *args[]={NULL};
	
	for(int i=0;i<n;i++)
	{
		sprintf(arg[i],"%d",a[i]);
	}
	printf("\nExexv : TO child");
	execv("./childout",args);

	printf("Back to parent\n");

	return 0;
}