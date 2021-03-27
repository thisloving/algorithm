#include <stdio.h>
#include <stdlib.h>

#define W_SRC 20

// 1
// B(k, w) = B(k-1, w)

// 2
// B(k, w) = B(k-1, w-wt[k]) + v[k]
// B(k, w) = B(k-1, w)
int knapsack(int wt_src[], int v_src[], int k_src) {
	const int K = k_src+1;
	int W = W_SRC+1;
	
	int i = 0;
	int j = 0;

	int wt[K];
	int v[K];

	wt[0] = 0;
	v[0] = 0;
	for (i = 1; i < K; i++) {
		wt[i] = wt_src[i-1];
		v[i] = v_src[i-1];
	}
	
	int k, w;
	int B[K][W];
	for (k = 0; k < K; k++) {
		for (w = 0; w < W; w++) {
			B[k][w] = 0;
		}
	}

	for (k = 1; k < K; k++) {
		for (w = 1; w < W; w++) {
			if (wt[k] > w) {
				B[k][w] = B[k-1][w];
			} else {
				int value1 = B[k-1][w-wt[k]] + v[k];
				int value2 = B[k-1][w];
				if (value1 > value2) {
					B[k][w] = value1;
				} else {
					B[k][w] = value2;
				}
			}
		}
	}

	return B[k_src][W_SRC];
}

int main() 
{
	int wt[] = {2, 3, 4, 5, 9};
	int v[] = {3, 4, 5, 8, 10};

	int k_src = sizeof(wt) / sizeof(wt[0]);
	
	int total = knapsack(wt, v, k_src);
	printf("%d\n", total);
}
