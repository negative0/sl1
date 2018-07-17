#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef MAX
#define MAX 10
#endif

void bubbleSort(int a[], int count){
	int i,j,temp;
	for(i=0;i<count-1;i++){
		for(j=0;j<count-i-1;j++){
			if(a[j]>a[j+1]){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}

		}
	}
}

int main(int argc, char const *argv[])
{
	int arr[MAX];
	int count = 0,i;
	char *options[20] = {"./child.out"};
		
		// options[1] = "\0";
	
	printf("Enter the number of elements:\t");
	
	scanf("%d",&count);
	// arr[0] = count;
	for(i=0;i<count;i++){
		scanf("%d",&arr[i]);
	}


	bubbleSort(arr, count);

	char *str_arr = (char*) malloc(100 * sizeof(char));
	char *ptr = str_arr;
	for(i=0;i<count;i++){
		char *temp = (char*) malloc(100);
		sprintf(temp, "%d", arr[i]);
		options[i+1] = temp;
	}
	options[count+1] = NULL;

	execv(options[0], options);
	//printf("%s %s", options[0], options[1]);


	return 0;
}
