#define MAX_SIZE 20
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
 
int is_empty(stack_type inputStack); //스택이 비었나 검사
int is_full(stack_type inputStack); //스택이 가득 찼나 검사
element pop(stack_type_ptr inputStack); //스택의 최상단 요소 삭제후 반환
void push(stack_type_ptr inputStack, element data); //스택의 값 넣기
element peek(stack_type inputStack); //스택 최상단 요소 확인

int main() {
	stack_type s; //스택 생성
	init(&s); //스택 초기화
	for (int i = 5; i < 100; i++) {
		push(&s, i); //push 를 100번 수행
	}
	while (!is_empty(s)) { //비어있지 않을때 까지 
		printf("%d \n", pop(&s)); //pop 수행 후 출력
	}
	free(s.data); //동적할당 한 data free

}



void init(stack_type_ptr inputStack) {  //stack 구조체를 초기화한다. 
	inputStack->top = -1; //초기화는 top 을 - 1 로 한다.
	inputStack->capacity = 1; //최대 인덱스 수를 1 로 만든다.
	inputStack->data = (element *)malloc(sizeof(element)*inputStack->capacity); //data 요소에 malloc 으로 메모리 공간 할당
}

void push(stack_type_ptr inputStack, element data) { //데이터를 넣는 함수

	if (is_full(*inputStack)) { //스택이 꽉찼으면
		inputStack->capacity *= 2; //capacity ( 최대 갯수) 를 증가시킨다. 2를 곱하는것이 메모리, 시피유 면에서 이득
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

