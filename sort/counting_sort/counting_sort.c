#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANGE 256

void counting_sort(char arr[]) {
	int n = strlen(arr);
	int i = 0;
	char output[n];
	int  count[RANGE];
	memset(count, 0, sizeof(count));

	for (i = 0; i < n; i++) {
		count[arr[i]]++;
	}

	for (i = 1; i < RANGE; i++) {
		count[i] += count[i-1]; 
	}

	for (i = n-1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}

	for (i = 0; i < n; i++) {
		arr[i] = output[i];
	}
}

int main() 
{
	char arr[] = "mnbvcxzlkjhgfdsaapouytrewq";
	counting_sort(arr);
	printf("%s\n", arr);
}
