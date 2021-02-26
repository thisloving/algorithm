#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insert_sort(int arr[], int n) {
	int i = 0;
	int j = 0;
	int temp = 0;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0; j--) { //Better understanding
			if (arr[j-1] > arr[j]) {
				swap(&arr[j-1], &arr[j]);
			} else {
				break;
			}
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
	int arr[] = {9, 7, 8, 6, 5, 3, 4, 2, 1};
	int n = sizeof(arr) / sizeof(arr[0]);
	insert_sort(arr, n);
	print_array(arr, n);

	return 0;
}
