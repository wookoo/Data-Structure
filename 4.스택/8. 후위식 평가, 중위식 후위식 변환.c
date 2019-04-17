#include <stdio.h>
#define MAXSIZE 100
typedef double element;
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
		return 0;
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

char get_symbols(char s[100]) {
	static int indexs = 0;
	if (s[indexs] != NULL) {
		return s[indexs++];
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
		;
		if (token == -1) {
			//printf("%c", sym);
			String[index++] = sym;
		}
		else if (token == 1 || token == 2) {
			while (is_empty(stack) != 1 && pie(peek(stack)) >= token) {
				//printf("%c", );
				String[index++] = pop(&stack);
			}
			push(&stack, sym);
		}
	}
	while (is_empty(stack) != 1) {
		String[index++] = pop(&stack);
		//printf("%c", pop(&stack));
	}
}

double eval(char s[100]) {
	char sym;
	Stack stack;
	initStack(&stack);

	while ((sym = get_symbols(s)) != NULL) {
		int token = pie(sym);
		if (token == -1) {
			push(&stack, (double)(sym - 48));
			//printf("push 수행끝");
		}
		else {
			double left = pop(&stack);

			double now = pop(&stack);
			double result;
			switch (sym) {
			case '+': push(&stack, left + now);
				break;
			case '-': push(&stack, now - left);
				break;
			case '*':
				result = left * now;
				push(&stack, result);

				break;
			case '/': push(&stack, now / left);
				break;
			case '%': push(&stack, (int)now % (int)left);
				break;
			}
		}
	}
	double temp = pop(&stack);
	//printf("%lf", temp);
	return temp;

}



int main(void)
{
	char String[] = "5+3*2";
	postfix(&String);
	printf("후위식 표기 : %s\n", String);
	printf("후위식 평가 : %lf", eval(String));
}
