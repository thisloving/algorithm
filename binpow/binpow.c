#include <stdio.h>
#include <stdlib.h>

long long binpow(int a, int b, int m) {
	int res = 1;

	a = a%m;
	while (b > 0) {
		if (b&1) {
			res = res*a%m;
		}
		a = a*a%m;

		b = b >> 1;
	}

	return res;
}

int main() {
	int a = 2;
	int b = 200;
	int m = 3;

	long long r = binpow(a, b, m);
	printf("%ld\n", r);
}
