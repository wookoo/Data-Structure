#include <stdio.h>
#include <string.h>
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
	case '(': return 0;
	case ')': return 3;
	case '+':case'-': return 1;
	case '*':case'%':case'/': return 2;
	}
	return -1;
}
int pie(char sym) { //잘 보면 59 번 60번 라인과 68번 69번 라인의 리턴값이 바뀐것을 볼 수 있다.
	switch (sym) {
	case '(': return 3;
	case ')': return 0;
	case '+':case'-': return 1;
	case '*':case'%':case'/': return 2;
	}
	return -1;
}
int main() {
	Stack stack;
	initStack(&stack);
	char String[100] = "5+4*(75+4)-5";
	char temp[100] = "";
	//strcpy(temp, String); //값 복사
	char sym;
	int index = 0;
	while ((sym = get_symbol(String)) != NULL) {
		//여기 수정
		
		int token = pie(sym);
		if (sym == ')') {
			char left;
			while ((left = pop(&stack)) != '(') {
				//printf(" %c", left);
				temp[index] = ' ';
				temp[++index] = left;
				temp[++index] = NULL;
			}
		}
		else if (pie(sym) == -1) {
			//printf("%c", sym);
			temp[index] = sym;
			temp[++index] = NULL;
		}
		else {
			if (sym != '(' && sym != ')') {
				//printf(" ");
				temp[index] = ' ';
				temp[++index] = NULL;
			}
			while ((is_empty(stack) != 1) && (pis(peek(stack)) >= pie(sym))) {
				//printf("%c ", pop(&stack));
				//temp[index] = ' ';
				temp[index] = pop(&stack);
				temp[++index] == ' ';
				temp[++index] = NULL;
			}
			push(&stack, sym);
		}

	}
	while (is_empty(stack) != 1) {
		temp[index] = ' ';
		temp[++index] = pop(&stack);
		temp[++index] = NULL;
		//printf(" %c", pop(&stack));
	}
	//temp[index] = '1';
	//temp[++index] = NULL;
	printf("%s", temp);


}
