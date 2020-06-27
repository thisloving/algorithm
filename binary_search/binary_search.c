#include <stdio.h>
#include <stdlib.h>

int binary_search(int *array, int n, int value) {
	int begin = 0;
	int end = n;
	int mid = 0;	

	while(begin < end) {
		mid = begin + (end-begin)/2;
		if (value < array[mid]) {
			end = mid;
		} else if (value > array[mid]) {
			begin = mid + 1;
		} else {
			return mid;
		}
	}

	return -1;
}

int main()
{
	int array[] = {1, 2, 3, 4, 5, 6, 7};
	int n = sizeof(array) / sizeof(int);

	int index = binary_search(array, n, 8);
	if (-1 == index) {
		printf("not found\n");
	} else {
		printf("%d\n", index);
	}

	return 0;
}
