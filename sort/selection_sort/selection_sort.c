#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *array, int n) {
	if (n <= 1) {
		return;
	}

	int begin 	= 0;
	int end 	= 0;
	
	for (end = n-1; end > 0; --end) {
		int max_index = 0;

		for (begin = 1; begin <= end; ++begin) {
			if (array[max_index] <= array[begin]) {
				max_index = begin;
			}
		}

		int tmp 			= array[max_index];
		array[max_index] 	= array[end];
		array[end] 			= tmp;
	}
}

int main() 
{
	int array[] = {56, 9, 10, 19, 28, 37, 34};                                   
	int n = sizeof(array) / sizeof(n);   

	selection_sort(array, n);

	int i = 0;                                                                   
	for (i = 0; i < n; ++i) {                                                    
		printf("%d ", array[i]);                                                 
	}                                                                            
	printf("\n"); 

	return 0;
}
