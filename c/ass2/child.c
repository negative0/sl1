#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef MAX
#define MAX 10
#endif

int binarySearch(int a[], int l, int r, int search){
	int mid = l-r;
	while(l<=r){
		mid = (l+r)/2;
		if(a[mid]==search){
			return mid;
		}else{
			if(a[mid]>search){
				r = mid+1;
			}else{
				l = mid-1;
			}
		}
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	
	int count = 0,i;
	int arr[MAX];
	char *options[2];
	int search,result;

	printf("In child\n");
	for(i = 1; i<argc;i++){
		// printf("%d:%s\n",i,argv[i]);
		arr[i-1] = atoi(argv[i]);
	}
	count = argc - 1;

	for(i = 0;i<count;i++){
		printf("%d: %d\n", i, arr[i]);
	}
	printf("Enter Element to be searched:\t");
	scanf("%d", &search);

	result = binarySearch(arr,0,count-1,search);

	if(result != 0){
		printf("Element found!\n"); 
	}
	else{
		printf("Element not found!\n"); 

	}


	// sleep(100);
		
	
}
