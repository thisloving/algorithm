#include <stdio.h>
#include <stdlib.h>

int binary_search(int *array, int n, int value) {
	if (n == 0) {
		return -1;
	}

	int lo  = 0;
	int hi  = n-1;
	int mid = 0;	

	while(lo <= hi) {
		mid = lo + (hi-lo)/2;
		if (value < array[mid]) {
			hi = mid - 1;
		} else if (value > array[mid]) {
			lo = mid + 1;
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

	int index = binary_search(array, n, 7);
	if (-1 == index) {
		printf("not found\n");
	} else {
		printf("%d\n", index);
	}

	return 0;
}
