#include <stdio.h>
#include <stdlib.h>


void shell_sort(int arr[], int n) {
	int gap  = 0;
	int i    = 0;
	int j    = 0;
	int temp = 0;
	
	for (gap = n/2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i++) {
			temp = arr[i];
			for (j = i; j-gap>=0 && arr[j-gap]>temp; j-=gap) {
				arr[j] = arr[j-gap];
			}
			arr[j] = temp;
		}
	}
}

void print_array(int arr[], int n) {
	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[] = {9, 7, 8, 6, 5, 4, 3, 2, 1};
	int n = sizeof(arr) / sizeof(arr[0]);

	shell_sort(arr, n);
	print_array(arr, n);
}
