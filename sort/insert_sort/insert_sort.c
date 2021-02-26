#include <stdio.h>
#include <stdlib.h>

void insert_sort(int arr[], int n) {
	int i = 0;
	int j = 0;
	int temp = 0;
	int gap  = 1; 
	for (i = gap; i < n; i++) {
		temp = arr[i];
		for (j = i-gap; j >= 0 && arr[j] > temp; j-=gap) { //Better understanding
			arr[j+gap] = arr[j];
		}

		arr[j+gap] = temp;
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
	int arr[] = {9, 7, 8, 6, 5, 3, 4, 2, 1};
	int n = sizeof(arr) / sizeof(arr[0]);
	insert_sort(arr, n);
	print_array(arr, n);

	return 0;
}
