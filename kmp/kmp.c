#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prefix_table(char pattern[], int prefix[], int n) {
	prefix[0] = 0;
	int len   = 0;
	int i     = 1;
	while (i < n) {
		if (pattern[i] == pattern[len]) {
			len++;
			prefix[i] = len;
			i++;
		} else {
			if (len > 0) {
				len = prefix[len-1];
			} else {
				prefix[i] = len; // len=0
				i++;
			}
		}
	}
}

void move_prefix_table(int prefix[], int n) {
	int i;
	for(i = n-1; i > 0; i--) {
		prefix[i] = prefix[i-1];
	}
	prefix[0] = -1;
}

void kmp_search(char text[], char pattern[]) {
	int  m = strlen(text);
	int  n = strlen(pattern);
	int* prefix = (int*)malloc(sizeof(int) * n);
	int i = 0;
	for(i = 0; i < n; i++) {
		prefix[i] = 0;
	}
	prefix_table(pattern, prefix, n);	
	move_prefix_table(prefix, n);

	for(i = 0; i < n; i++) {
		printf("%d ", prefix[i]);
	}
	printf("\n");

	i = 0;
	int j = 0;
	bool found = false;
	while (i < m) {
		if (j == n - 1 && text[i] == pattern[j]) {
			printf("Found pattern at %d\n", i - j);
			found = true;
			j = prefix[j];
		}

		if (text[i] == pattern[j]) {
			//printf("equal text=%d pattern:%d\n", i, j);
			i++;
			j++;
		} else {
			j = prefix[j];
			if (j == -1) {
				i++;
				j++;
				printf("i:%d j:-1\n", i);
			}
			//printf("not equal text:%d pattern:%d\n", i, j);
		}
	}

	if (!found) {
		printf("Not found pattern\n");
	}
}

int main() 
{
	char pattern[] = "ABABCABAA";
	char text[]    = "ABABABCABAAABABAB";

	kmp_search(text, pattern);

	return 0;
}

