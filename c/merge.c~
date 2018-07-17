/* C program for Merge Sort */
#include<stdlib.h>
#include<stdio.h>
#define MAX 10
 
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}
 
/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}
 
/* Driver program to test above functions */
int main()
{
    int i,arr[MAX];
    int arr_size;
    int status;
    printf("Enter the no of elements max:%d",MAX);
    scanf("%d",&arr_size);
    printf("Enter Elements:\t");
    for(i=0;i<arr_size;i++){
    	scanf("%d",&arr[i]);
    }
    status = fork();
    if(status != 0){
	    printf("Merge Sort in Parent: PID,PPID: %d, %d\n",getpid(),getppid());
	     sleep(10);

	    printf("Given array is \n");
	    printArray(arr, arr_size);
	 
	    mergeSort(arr, 0, arr_size - 1);
	    printf("Parent Output :");
	    //printf("\nSorted array is \n");
	    printArray(arr, arr_size);
	    printf("Parent Exiting\n");
	    //sleep(10);
	    exit(-1);
	    system("wait");
	    system("ps -elf | grep merge");
    }else{
    	printf("Child Executing!\n");
    	printf("Insertion Sort in child: PID, PPID:%d, %d\n",getpid(),getppid());
    	
    	insertionSort(arr, arr_size);
    	sleep(20);
    	printf("Child Output :");
    	printArray(arr, arr_size);
	
	printf("Stopping child\n");
    }
    
    return 0;
}

