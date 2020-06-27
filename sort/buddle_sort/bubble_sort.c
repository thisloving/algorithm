#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble_sort(int* array, int n) {
	if (n <= 1) {
		return;
	}

	int begin 	= 0;
	int end 	= 0;
	for (end = n - 1; end > 0; --end) {
		int sorted_index = 1;

		for (begin = 1; begin <= end; ++begin) {
			if (array[begin] < array[begin-1]) {
				int tmp 		= array[begin];
				array[begin] 	= array[begin-1];
				array[begin-1] 	= tmp;

				sorted_index = begin;
			}
		}

		end = sorted_index;
	}
}

int main() 
{
	int array[] = {56, 9, 10, 19, 28, 37, 34};
	int n = sizeof(array) / sizeof(n);

	bubble_sort(array, n);

	int i = 0;
	for (i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

