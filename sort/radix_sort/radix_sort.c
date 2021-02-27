#include <stdio.h>
#include <stdlib.h>

void print_array(int arr[], int n);

int get_max(int arr[], int n) {
	int max = 0;
	int i = 0;
	for (i = 0; i < n; i++) {
		if (max < arr[i]) {
			max = arr[i];
		}
	}
	return max;
}

void count_sort(int arr[], int n, int rem) {	
	int output[n];
	int count[10] = {0};
	int i   = 0;
	int num = 0;
	
	for (i = 0; i < n; i++) {
		num = (arr[i]/rem) % 10;	
		count[num]++;
	}

	for (i = 1; i < 10; i++) {
		count[i] += count[i-1];
	}

	//for (i = 0; i < n; i++) { // This is wrong
	for (i = n-1; i >= 0; i--) {
		num = (arr[i]/rem) % 10;
		output[count[num]-1] = arr[i];
		count[num]--;
	}

	for (i = 0; i < n; i++) {
		arr[i] = output[i];
	}
}

void radix_sort(int arr[], int n) {
	int max = get_max(arr, n);
	int i = 0;
	for (i = 1; max/i > 0; i *= 10) {
		count_sort(arr, n, i);
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
	int arr[] = {987, 654, 321, 910, 864, 345};
	int n = sizeof(arr)/sizeof(arr[0]);

	radix_sort(arr, n);
	print_array(arr, n);
}
