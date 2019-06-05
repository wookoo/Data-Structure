#include <stdio.h>
#include <stdlib.h>
typedef union
{
	int number;
	char sign;

}element;
int eval(element* arr) {

}
int is_char(int data) {
	switch (data)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '%': return 1;
	}
	return 0;
}

void postorder(element* arr, int index) {
	if (arr[index].number != 0) {
		postorder(arr, 2 * index);
		postorder(arr, 2 * index + 1);
		if (is_char(arr[index].number)) {
			printf("[%c]", arr[index].sign);
		}
		else {
			printf("[%d]", arr[index].number);
		}

		
	}
}
void preorder(element* arr, int index) {
	if (arr[index].number != 0) {
		if (is_char(arr[index].number)) {
			printf("[%c]", arr[index].sign);
		}
		else {
			printf("[%d]", arr[index].number);
		}
		preorder(arr, 2 * index);
		preorder(arr, 2 * index + 1);
	}
}

void inorder(element* arr, int index) {
	if (arr[index].number != 0 ) {
		inorder(arr, 2 * index);
		if (is_char(arr[index].number)) {
			printf("[%c]", arr[index].sign);
		}
		else {
			printf("[%d]", arr[index].number);
		}
		
		inorder(arr, 2 * index + 1);
	}
}

int main() {
	element arr[16] = { NULL,'+','*','/',3,2,5,6 };
	inorder(arr,1);
	printf("\n");
	postorder(arr, 1);
	printf("\n");
	preorder(arr, 1);

}
