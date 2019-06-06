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

int pie(char sym) {
	switch (sym) {
	case '+':case '-': return 1;
	case '*':case '%':case '/': return 2;
	}
	return -1;
}

void postfix(char *String) {
	Stack stack;
	initStack(&stack);

	char sym;
	int index = 0;
	while ((sym = get_symbol(String)) != NULL) {
		int token = pie(sym);
		
		if (token == -1) {
	
			String[index++] = sym;
		}
		else if (token == 1 || token == 2) {
			while (is_empty(stack) != 1 && pie(peek(stack)) >= token) {
		
				String[index++] = pop(&stack);
			}
			push(&stack, sym);
		}
	}
	while (is_empty(stack) != 1) {
		String[index++] = pop(&stack);
	}
}

int main(void)
{
	char String[] = "5+3*2";
	/*
	1. 수식을 입력 받고
	2. 수식을 후위식으로 변환하고 > 스택 사용
	>> 수식이 숫자이면 계속 스트링에 붙이기
	>> 수식이 문자면 atoi 를 사용해서 숫자 할당하기 >> strlen 사용
	3. 변환된 수식으로 트리를 구성하고
	4. 그 트리를 평가
	
	*/
	postfix(&String);
	printf("%s", String);
}
