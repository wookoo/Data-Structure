#include <stdio.h>
#include <stdlib.h>
typedef int element; //elemnet ����, �ٸ� Ÿ���� ������ ���鶩  int �� ����

typedef struct {
	element *data; //data �� �����ͷ� �޴´�
	int top; //data �ε���
	int capacity;  //data �� �ִ� ũ��
} stack_type;

typedef stack_type* stack_type_ptr; //�Լ� ������ ��Ÿ������ ����

void init(stack_type_ptr inputStack); //���� �ʱ�ȭ
int pie(char sym);
int pis(char sym);
char get_symbol(char *s);
int is_empty(stack_type inputStack); //������ ����� �˻�
int is_full(stack_type inputStack); //������ ���� á�� �˻�
element pop(stack_type_ptr inputStack); //������ �ֻ�� ��� ������ ��ȯ
void push(stack_type_ptr inputStack, element data); //������ �� �ֱ�
element peek(stack_type inputStack); //���� �ֻ�� ��� Ȯ��
void postfix(char *exp,char *post_exp);
int main() {
	
	//char exp[100];
	//scanf("%s", exp);
	char exp[] = "5+45*(7+4)-5";
	char post_exp[100];

	postfix(exp, post_exp); // ���� ������ ��ȯ
	printf("\n%s", post_exp);
	//res = eval(post_exp);
//	postfix(exp);
	
}



void init(stack_type_ptr inputStack) {  //stack ����ü�� �ʱ�ȭ�Ѵ�. 
	inputStack->top = -1; //�ʱ�ȭ�� top �� - 1 �� �Ѵ�.
	inputStack->capacity = 1; //�ִ� �ε��� ���� 1 �� �����.
	inputStack->data = (element *)malloc(sizeof(element)*inputStack->capacity); //data ��ҿ� malloc ���� �޸� ���� �Ҵ�
}

void push(stack_type_ptr inputStack, element data) { //�����͸� �ִ� �Լ�

	if (is_full(*inputStack)) { //������ ��á����
		inputStack->capacity *= 2; //capacity ( �ִ� ����) �� ������Ų��. 2�� ���ϴ°��� �޸�, cpu �鿡�� �̵�
		inputStack->data = (element *)realloc(inputStack->data, sizeof(element)*inputStack->capacity);
		//realloc �� �ҷ� �޸� ������ �÷��ش�.
	}
	inputStack->top += 1; //���� �����Ƿ� top ������
	inputStack->data[inputStack->top] = data; //���� �Ҵ�

}


int is_empty(stack_type inputStack) {
	return ((inputStack.top == -1)); //������ top �� -1 �̸� ��, �ƴϸ� ����
}

int is_full(stack_type inputStack) {
	return  (inputStack.top == (inputStack.capacity - 1)); //������ top �� ������ capacity -1 �̸� ��, �ƴϸ� ����
}


element pop(stack_type_ptr inputStack) {

	if (is_empty(*inputStack)) { //������ �������
		printf("���̻� ����� �����ϴ�!"); //pop���� �Ұ��� ���α׷� ���� ����
		exit(1);
	}
	else {
		element returnData = inputStack->data[inputStack->top];
		inputStack->top -= 1;

		return returnData; //������ �ֻ�� �� ������ ��ȯ
	}

}
element peek(stack_type inputStack) {
	if (is_empty(inputStack)) { //������ �������
		printf("���� �����ϴ�!"); //���� �����Ƿ� ���� ����
		exit(1);
	}
	return inputStack.data[inputStack.top]; //������ �ֻ�� �� ��ȯ
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
int pie(char sym) { //�� ���� 59 �� 60�� ���ΰ� 68�� 69�� ������ ���ϰ��� �ٲ���� �� �� �ִ�.
	switch (sym) {
	case '(': return 3;
	case ')': return 0;
	case '+':case'-': return 1;
	case '*':case'%':case'/': return 2;
	}
	return -1;
}
char get_symbol(char *s) {
	static int index = 0;
	if (s[index] != NULL) {
		return s[index++];
	}
	return NULL;
}




void postfix(char *exp,char *post_exp) {
	stack_type s; //���� ����
	init(&s); //���� �ʱ�ȭ
	char sym;
	int index = 0;
	post_exp[index] = NULL;
	while ((sym = get_symbol(exp)) != NULL) {
		int token = pie(sym);
		if (sym == ')') {
			char left;

			while ((left = pop(&s)) != '(') {
				printf(" %c", left);
				post_exp[index++] = ' ';
				post_exp[index++] = left;
				post_exp[index] = NULL;

			}
			

		}
		else if (pie(sym) == -1) {
			printf("%c", sym);
			post_exp[index++] = sym;
			post_exp[index] = NULL;
		}
		else {
			if (sym != '(' && sym != '(') {
				printf(" ");
				post_exp[index++] = ' ';
				post_exp[index] = NULL;
			}
			while ((is_empty(s) != 1) && (pis(peek(s)) >= pie(sym))) {
				char temp = pop(&s);
				printf("%c ", temp);
				post_exp[index++] = temp;
				post_exp[index++] = ' ';
				post_exp[index] = NULL;
			}
			push(&s, sym);


		}

	}

	while (is_empty(s) != 1) {
		char temp = pop(&s);
		printf(" %c", temp);
		post_exp[index++] = ' ';
		post_exp[index++] = temp;
		post_exp[index] = NULL;
	}



	free(s.data); //�����Ҵ� �� data free
}