#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selection_sort(int arr[], int n) {
	if (n <= 1) {
		return;
	}

	int i = 0;
	int j = 0;
	int min = 0;

	for (i = 0; i < n-1; i++) {
		min = i;
		for (j = i+1; j < n; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		swap(&arr[i], &arr[min]);
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
	int arr[] = {56, 9, 10, 19, 28, 37, 34};                                   
	int n = sizeof(arr) / sizeof(n);   

	selection_sort(arr, n);
	print_array(arr, n);
	
	return 0;
}
