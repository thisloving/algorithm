#include <stdio.h>
#include <stdlib.h>

void insert_sort(int *array, int n) {
	if (n <= 1) {
		return;
	}

	int begin = 0;

	for (begin = 1; begin < n; ++begin) {
		int cur = begin;
		while (cur > 0 && array[cur] < array[cur-1]) {
			int tmp 		= array[cur];
			array[cur] 	= array[cur-1];
			array[cur-1] 	= tmp;
			
			--cur;
		}
	}
}

void insert_sort_optimize(int *array, int n) {
	if (n <= 1) {
		return;
	}

	int begin = 0;

	for (begin = 1; begin < n; ++begin) {
		int cur = begin;
		int cur_value = array[cur];
		while (cur > 0 && cur_value < array[cur-1]) {
			array[cur] = array[cur-1];
			--cur;
		}

		array[cur] 	= cur_value;
	}
}

int binary_search(int *array, int index, int value) {
	int begin = 0;
	int end = index;
	int mid = 0;	

	while(begin < end) {
		mid = begin + (end-begin)/2;
		if (array[index] < array[mid]) {
			end = mid;
		} else { 
			begin = mid + 1;
		} 
	}

	return begin;
}

int insert_sort_optimize_by_binary_search(int *array, int n) {
	int begin 		= 0;
	int cur_value 	= 0;

	for (begin = 1; begin < n; ++begin) {
		cur_value = array[begin];
		int i = 0;
		int index = binary_search(array, begin, cur_value);
		for (i = begin; i >= index ; --i) {
			array[i] = array[i-1];
		}
		array[index] = cur_value;
	}
}

int main() 
{
	int array[] = {14, 36, 7, 11, 47, 15, 66, 35, 37, 23, 92, 5, 26, 37, 83, 27};
	int n = sizeof(array) / sizeof(int);

	insert_sort_optimize_by_binary_search(array, n);

	int i = 0;                                                                   
	for (i = 0; i < n; ++i) {                                                    
		printf("%d ", array[i]);                                                 
	}                                                                            
	printf("\n"); 

	return 0;
}
