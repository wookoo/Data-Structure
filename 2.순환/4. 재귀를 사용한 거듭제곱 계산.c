#include <stdio.h>
int power(double x, int n) {
	if (n == 0) return 1;
	else if (n % 2 == 0) 
		return power(x*x, n / 2);
	else return x * power(x*x, (n - 1) / 2);
}

int main() {
	printf("%d", power(5,2));
}