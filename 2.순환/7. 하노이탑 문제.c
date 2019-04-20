#include <stdio.h>
void hanoi(int n, char from, char temp, char to) {
	if (n == 1) {
		printf("원판 %d 을 %c 에서 %c 로 옮긴다.\n", n, from, to);
	}
	else {
		hanoi(n - 1, from, to, temp);
		printf("원판 %d 을 %c 에서 %c 로 옮긴다.\n", n, from, to);
		hanoi(n - 1, temp, from, to);
	}
}
int main() {
	hanoi(3,'A','B','C');
}