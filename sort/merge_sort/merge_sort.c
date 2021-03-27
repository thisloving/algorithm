#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
	int n1 = m-l+1;
	int n2 = r-m;

	int L[n1], R[n2];

	int i = 0;
	for (i = 0; i < n1; i++) {
		L[i] = arr[l+i];
	}
	int j = 0;
	for (j = 0; j < n2; j++) {
		R[j] = arr[m+1+j];
	}

	i = 0;
	j = 0;
	int k = l;
	while (i < n1 && j < n2) {
		if (L[i] < R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void merge_sort(int arr[], int l, int r) {
	if (l >= r) {
		return;
	}

	int m = l+(r-l)/2;
	merge_sort(arr, l, m);
	merge_sort(arr, m+1, r);
	merge(arr, l, m, r);
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
	int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	int n = sizeof(arr) / sizeof(arr[9]);

	merge_sort(arr, 0, n-1);
	print_array(arr, n);

	return 0;
}
