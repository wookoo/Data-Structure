#include <stdio.h>
#define MAXSIZE 100
typedef int element;
typedef struct {
	element data[MAXSIZE];
	int top;
}Stack;

typedef Stack* Stack_Ptr;

void initStack(Stack_Ptr StackPointer) {
	StackPointer->top = -1;
}


int  is_empty(Stack stack) {
	return (stack.top == -1);
}

element pop(Stack_Ptr StackPointer) {
	if (is_empty(*StackPointer)) {
		printf("더이상 pop 을 수행할수 없습니다.");
		exit(1);
	}
	element temp = StackPointer->data[StackPointer->top];
	StackPointer->top -= 1;
	return temp;
}

void push(Stack_Ptr StackPointer, element data) {
	if (is_full(*StackPointer)) {
		printf("더이상 push 를 수행 할 수 없습니다.");
		exit(1);
	}
	StackPointer->top += 1;
	StackPointer->data[StackPointer->top] = data;
}

int is_full(Stack stack) {
	return(stack.top == MAXSIZE);
}

element peek(Stack stack) {
	if (is_empty(stack)) {
		return NULL;
	}
	return (stack.data[stack.top]);
}

char get_symbol(char s[100]) {
	static int index = 0;
	if (s[index] != NULL) {
		return s[index++];
	}
	return NULL;
}

int pis(char sym) {
	switch (sym) {
	case '(':return 0;
	case '+':case '-': return 1;
	case '*':case '%':case '/': return 2;
	}
	return -1;
}

int pie(char sym) {
	switch (sym) {
	case '(':return 3;
	case '+':case '-': return 1;
	case '*':case '%':case '/': return 2;
	}
	return -1;
}



int main(void)
{
	Stack stack;
	initStack(&stack);
	char String[] = "5*42*4/91";
	char sym;
	while ((sym = get_symbol(String)) != NULL) {
		int token = pie(sym);
		//printf("  심볼 : %c   token 리턴 %d  흠  : ", sym,token);
		if (token == -1 && sym !=')') printf("%c", sym);

		else if (token == 1 || token == 2 ) {
			while (is_empty(stack) != 1 && pis(peek(stack)) >= token) {
				printf("%c", pop(&stack));
			}
			push(&stack, sym);
		}
		else {
			char left = pop(&stack);
			printf("%c", left);
			while (is_empty(stack) != 1 && left != '(') {
				printf("%c", left);
			}
		}


	}
	while (is_empty(stack) != 1) {
		printf("%c", pop(&stack));
	}





}
