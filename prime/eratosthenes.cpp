#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const static int MAX_NUM = 100;

void eratosthenes(int upperbound) {
	std::vector<bool> flag(upperbound+1, true);
	flag[0] = flag[1] = false;
	for (int i = 2; i < sqrt(upperbound); ++i) {
		if (flag[i]) {
			for (int j = i*i; j <= upperbound; j+=i) {
				flag[j] = false;
			}
		}
	}
	
	for (int i = 0; i <= upperbound; ++i) {
		if (flag[i]) {
			cout << i << " ";
		}
	}

	cout << endl;
}

int main() {
	eratosthenes(MAX_NUM);

	return 0;
}
