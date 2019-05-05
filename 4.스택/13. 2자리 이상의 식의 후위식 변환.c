#include <stdio.h>
#include <stdlib.h>
typedef int element; //elemnet 정의, 다른 타입의 스택을 만들땐  int 만 수정

typedef struct {
	element *data; //data 를 포인터로 받는다
	int top; //data 인덱스
	int capacity;  //data 의 최대 크기
} stack_type;

typedef stack_type* stack_type_ptr; //함수 포인터 새타입으로 정의

void init(stack_type_ptr inputStack); //스택 초기화
int pie(char sym);
int pis(char sym);
char get_symbol(char *s);
int is_empty(stack_type inputStack); //스택이 비었나 검사
int is_full(stack_type inputStack); //스택이 가득 찼나 검사
element pop(stack_type_ptr inputStack); //스택의 최상단 요소 삭제후 반환
void push(stack_type_ptr inputStack, element data); //스택의 값 넣기
element peek(stack_type inputStack); //스택 최상단 요소 확인
void postfix(char *exp,char *post_exp);
int main() {
	
	//char exp[100];
	//scanf("%s", exp);
	char exp[] = "5+45*(7+4)-5";
	char post_exp[100];

	postfix(exp, post_exp); // 후위 식으로 변환
	printf("\n%s", post_exp);
	//res = eval(post_exp);
//	postfix(exp);
	
}



void init(stack_type_ptr inputStack) {  //stack 구조체를 초기화한다. 
	inputStack->top = -1; //초기화는 top 을 - 1 로 한다.
	inputStack->capacity = 1; //최대 인덱스 수를 1 로 만든다.
	inputStack->data = (element *)malloc(sizeof(element)*inputStack->capacity); //data 요소에 malloc 으로 메모리 공간 할당
}

void push(stack_type_ptr inputStack, element data) { //데이터를 넣는 함수

	if (is_full(*inputStack)) { //스택이 꽉찼으면
		inputStack->capacity *= 2; //capacity ( 최대 갯수) 를 증가시킨다. 2를 곱하는것이 메모리, cpu 면에서 이득
		inputStack->data = (element *)realloc(inputStack->data, sizeof(element)*inputStack->capacity);
		//realloc 을 불러 메모리 공간을 늘려준다.
	}
	inputStack->top += 1; //값을 넣으므로 top 증가후
	inputStack->data[inputStack->top] = data; //값을 할당

}


int is_empty(stack_type inputStack) {
	return ((inputStack.top == -1)); //스택의 top 이 -1 이면 참, 아니면 거짓
}

int is_full(stack_type inputStack) {
	return  (inputStack.top == (inputStack.capacity - 1)); //스택의 top 이 스택의 capacity -1 이면 참, 아니면 거짓
}


element pop(stack_type_ptr inputStack) {

	if (is_empty(*inputStack)) { //스택이 비었으면
		printf("더이상 지울수 없습니다!"); //pop수행 불가로 프로그램 강제 종료
		exit(1);
	}
	else {
		element returnData = inputStack->data[inputStack->top];
		inputStack->top -= 1;

		return returnData; //스택의 최상단 값 삭제후 반환
	}

}
element peek(stack_type inputStack) {
	if (is_empty(inputStack)) { //스택이 비었으면
		printf("값이 없습니다!"); //값이 없으므로 강제 종료
		exit(1);
	}
	return inputStack.data[inputStack.top]; //스택의 최상단 값 반환
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
char get_symbol(char *s) {
	static int index = 0;
	if (s[index] != NULL) {
		return s[index++];
	}
	return NULL;
}




void postfix(char *exp,char *post_exp) {
	stack_type s; //스택 생성
	init(&s); //스택 초기화
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



	free(s.data); //동적할당 한 data free
}