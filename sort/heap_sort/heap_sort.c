#include <stdio.h>
#include <stdlib.h>

void swap(int *arr, int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void heapify(int *tree, int n, int i) {
	if (i >= n) {
		return;
	}

	int c1 = 2*i+1;
	int c2 = 2*i+2;

	int max = i;
	if (c1 < n && tree[c1] > tree[max]) {
		max = c1;
	}
	if (c2 < n && tree[c2] > tree[max]) {
		max = c2;
	}

	if (max != i) {
		swap(tree, max, i);
		heapify(tree, n, max);
	}
}

void build_heap(int *array, int n) {
	if (n <= 1) {
		return;
	}

	int last_node = n - 1;
	int parent = (last_node - 1) / 2;
	int i = 0;
	for (i = parent; i >= 0; i--) {
		heapify(array, n, i);
	}
}

void heap_sort(int *array, int n) {
	build_heap(array, n);
	int i = 0;
	for (i = n-1; i >= 0; i--) {
		swap(array, i, 0);
		heapify(array, i, 0);
	}
}

int main() 
{
	int array[] = {4, 10, 3, 5, 1, 2};
	int n = sizeof(array) / sizeof(int);
	
	heap_sort(array, n);

	int i = 0;
	for (i = 0; i< n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
