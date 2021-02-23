#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void quick_sort(int arr[], int left, int right) {
	if (left >= right) {
		return;
	}

	int pivot = arr[left];
	int i = left;;
	int j = right + 1;

	while (i < j) {
		while (pivot > arr[i]) {
			++i;
		}

		while (pivot < arr[j]) {
			--j;
		}

		if (i < j) {
			swap(&arr[i], &arr[j]);
		}
	}

	while (i < j) {
		swap(&arr[i], &arr[j]);
	}
	
	quick_sort(arr, left, j-1);
	quick_sort(arr, j+1, right);
}

int main()
{
	int arr[] = {9, 8 ,7, 6, 5, 4, 3, 2, 1};
	int n = sizeof(arr) / sizeof(int);

	quick_sort(arr, 0, n-1);

	int i = 0;
	for (i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
