#include <stdio.h>
int power(double x, int n) {
	double result = 1.0;
	for (int i = 0; i < n; i++) {
		result *= x;
	}
	return result;
}

int main() {
	printf("%d", power(5,2));
}