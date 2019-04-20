#include <stdio.h>
int fibo(int n){
	if (n == 0) return 0;
	if (n == 1) return 1;
	int pp = 0;
	int p = 1;
	int result = 0;
	for (int i = 2; i <= n; i++) {
		result = pp + p;
		pp = p;
		p = result;
	}
	return result;
}

int main() {
	printf("%d", fibo(10));
}