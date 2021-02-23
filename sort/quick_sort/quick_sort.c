#include <stdio.h>
#include <stdlib.h>

int pivot_index(int *array, int begin, int end) {
	int pivot = array[begin];
	--end;

	while(begin < end) {
		while(begin < end) {
			if (pivot < array[end]) {
				--end;
			} else {
				array[begin] = array[end];
				++begin;
				break;
			}
		}

		while (begin < end) {
			if (pivot > array[begin]) {
				++begin;
			} else {
				array[end] = array[begin];
				--end;
				break;
			}
		}
	}

	array[begin] = pivot;
	return begin;
}

void quick_sort(int *array, int begin, int end) {
	if (end - begin < 2) {
		return;
	}

	int mid = pivot_index(array, begin, end);

	quick_sort(array, begin, mid);
	quick_sort(array, mid+1, end);
}

int main()
{
	int array[] = {33, 4, 5, 7, 3, 99, 87, 34, 23, 7, 8, 10};
	int n = sizeof(array) / sizeof(int);
	quick_sort(array, 0, n);

	int i = 0;
	for (i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
