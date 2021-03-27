#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bucket_sort(float arr[], int n) {
	vector<float> b[n];

	for (int i = 0; i < n; i++) {
		int bi = n * arr[i];
		b[bi].push_back(arr[i]);
	}
	
	for (int i = 0; i < n; i++) {
		sort(b[i].begin(), b[i].end());
	}

	int index = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < b[i].size(); j++) {
			arr[index++] = b[i][j];
		}
	}
}

void print_array(float arr[], int n) {
	int i = 0;
	for (i = 0; i < n; i++) {
		cout << arr[i] << " "; 
	}
	cout << endl;
}

int main() {
	float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
	int n = sizeof(arr)/sizeof(arr[0]);

	bucket_sort(arr, n);
	print_array(arr, n);
}
