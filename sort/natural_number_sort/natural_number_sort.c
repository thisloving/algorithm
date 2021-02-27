#include <stdio.h>
#include <stdlib.h>

void natural_number_sort(int arr[], int n) {
	int i = 0;
	int t = 0;
	for (i = 0; i < n; i++) {
		while (arr[i] != i+1) {
			t = arr[arr[i]-1];
			arr[arr[i]-1] = arr[i];
			arr[i] = t;
		}
	}
}

void print_array(int arr[], int n){
	int i = 0;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int n = sizeof(arr)/sizeof(arr[0]);

	natural_number_sort(arr, n);
	print_array(arr, n);
}
