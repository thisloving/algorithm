#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void repeatable_natural_number_sort(int arr[], int n) {
	int output[n];
	memset(output, 0, n);
	int i = 0;
	int count[10] = {0};

	for (i = 0; i < n; i++) {
		count[arr[i]]++;
	}

	for (i = 1; i < 10; i++) {
		count[i] += count[i-1];
	}

	for (i = n-1; i >= 0; i--) { // stable
		output[count[arr[i]]-1] = arr[i];
		count[arr[i]]--;
	}

	for (i = 0; i < n; i++) {
		arr[i] = output[i];
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
	int arr[] = {9, 9, 8, 8, 7, 7, 6, 6, 5, 5, 3, 4, 4, 3, 2, 2, 1, 1, 0};
	int n = sizeof(arr) / sizeof(arr[0]);

	repeatable_natural_number_sort(arr, n);
	print_array(arr, n);
}
