#include <stdio.h>
#include <stdlib.h>


void preorder(int *t,int index) {
	if (t[index] != 0) {
		printf("[%d]",t[index]);
		preorder(t, 2 * index);
		preorder(t, 2 * index + 1);
	}
}

void inorder(int *t, int index) {
	if (t[index] != 0) {
		inorder(t, 2 * index);
		printf("[%d]", t[index]);
		inorder(t, 2 * index + 1);
	}
}

void postorder(int *t,int index) {
	if (t[index] != 0) {
		postorder(t,2*index);
		postorder(t, 2 * index + 1);
		printf("[%d]", t[index]);
	}
}




int main() {
	int a[32] = { 0,5,4,7,9,6,0,3,0,2,0,0,0,0,1,0 };
	printf("전위 탐색 ");
	preorder(a, 1);
	printf("\n중위 탐색 ");
	inorder(a, 1);
	printf("\n후위 탐색 ");
	postorder(a, 1);
}
