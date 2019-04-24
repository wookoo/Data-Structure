#include <stdio.h>
#define MAX 100
#include <string.h>
typedef char elemant;
typedef struct {
	elemant data[MAX];
	int top;
}stack;
typedef stack* stack_ptr;

int is_empty(stack inputStack) {
	return (inputStack.top == -1);
}
int is_full(stack inputStack) {
	return (inputStack.top == MAX - 1);
}
elemant peek(stack inputStack) {
	if (is_empty(inputStack)) {
		printf("peek �� �����Ҽ� �����ϴ�.");
		exit();
	}
	return inputStack.data[inputStack.top];
}
void push(stack_ptr inputStack,elemant data) {
	if (is_full(*inputStack)) {
		printf("push �� ���� �� �� �����ϴ�.");
		exit();
	}
	inputStack->data[++(inputStack->top)] = data;
}
elemant pop(stack_ptr inputStack) {
	if (is_empty(*inputStack)) {
		printf("���̻� pop �� ���� �� �� �����ϴ�");
		exit();
	}
	return inputStack->data[(inputStack->top)--];
}
void init(stack_ptr inputStack) {
	inputStack->top = -1;
}
char get_symbol(char* String) {
	static int index = 0;
	if (String[index] != NULL) {
		return String[index++];
	}
	return NULL;
}

int is_palindrome(char* String) {
	char sym;
	stack s;
	init(&s);
	while ((sym = get_symbol(String)) != NULL) {
		push(&s, sym);
	}
	int index = 0;
	while (!is_empty(s)) {
		char temp = pop(&s);
		if (temp == String[index]) {
			index++;
		}
		else {
			return 0;
		}
	}
	return 1;
}


int main() {
	char String[] = "abcdedcba";
	if (is_palindrome(String)) {
		printf("%s �� ȸ���Դϴ�",String);
	}
	else {
		printf("%s �� ȸ���� �ƴմϴ�",String);
	}
}