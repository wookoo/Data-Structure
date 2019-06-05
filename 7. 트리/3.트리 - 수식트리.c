#include <stdio.h>
#include <stdlib.h>
typedef union
{
	int number;
	char sign;

}element;

int is_leaf(element *arr, int index) {
	return  (arr[2 * index].number == NULL && arr[2 * index + 1].number == NULL);
}

void postorder(element* arr, int index) {
	if (arr[index].number != 0) {
		postorder(arr, 2 * index);
		postorder(arr, 2 * index + 1);
		if (is_leaf(arr, index)) {
			printf("[%d]", arr[index].number);
		}
		else {
			printf("[%c]", arr[index].sign);
		}


	}
}
void preorder(element* arr, int index) {
	if (arr[index].number != 0) {
		if (is_leaf(arr, index)) {
			printf("[%d]", arr[index].number);
		}
		else {
			printf("[%c]", arr[index].sign);
		}
		preorder(arr, 2 * index);
		preorder(arr, 2 * index + 1);
	}
}

void inorder(element* arr, int index) {
	if (arr[index].number != 0) {
		inorder(arr, 2 * index);
		if (is_leaf(arr, index)) {
			printf("[%d]", arr[index].number);
		}
		else {
			printf("[%c]", arr[index].sign);
		}
		inorder(arr, 2 * index + 1);
	}
}

int eval(element *arr,int index) {
	if (arr[index].number == NULL) {
		return 0;
	}
	if (is_leaf(arr,index)) {
		return arr[index].number;
	}
	int op1 = eval(arr, 2 * index);
	int op2 = eval(arr, 2 * index + 1);
	//printf("%d %c %d 를 계산합니다\n", op1, arr[index].sign, op2);
	switch (arr[index].sign)
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}
	return 0;
}

int get_count(element *arr, int index) {
	if (arr[index].number != NULL) {
		return 1 + get_count(arr, index * 2) + get_count(arr, index * 2 + 1);
	}
	else {
		return 0;
	}
}

int main() {
	element arr[16] = { NULL,'+','*','/',3,2,30,6 };
	printf("중위 탐색 ");
	inorder(arr, 1);
	printf("\n후위 탐색");
	postorder(arr, 1);
	printf("\n전위 탐색");
	preorder(arr, 1);
	printf("\n계산결과 : ");
	printf("%d\n",eval( arr, 1));
	printf("잎노드 갯수 : %d", get_count(arr, 1));
}
