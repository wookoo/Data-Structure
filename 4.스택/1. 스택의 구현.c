/*
	* 문제
	*	스택을 구현해보자
	* 출력
	*	1 2 3 을 push 하고 pop 을 3번 호출해서 결과값을 본다,
	*알고리즘
	*	스택을 구현을 하는 것 이다.
	*	구조체를 사용하여 데이터가 들어가있는 배열과, 데이터의 인덱스 값을 저장한다.
	*	스택이 비지 않을때 까지 마지막으로 넣었던 값을 지우고 출력하는 pop 함수를 사용한다.
	*	push 함수 : 스택이 꽉차지 않았으면 데이터를 밀어 넣는다. 꽉차면 밀어넣지 못한다. top 을 + 1
	*	pop 함수 : 스택이 비어있지 않았으면 데이터를 삭제한다. 비었으면 삭제하지 못한다. top 을 - 1
	*	is_empty 함수 : stack 이 비었는지 확인한다. top 이 -1 이면 빈 스택이다.
	*	is_full 함수 : stack 이 꽉찼는지 확인한다. top 이 구조체가 가진 배열의 MAX 면 꽉찬 스택이다.
	*함수
	*	void init(stack_type_ptr inputStack) : stack 을 초기화한다.
	*	void push(stack_type_ptr inputStack, element data) : stack에 받아온 data 를 넣는다.
	*	int is_empty(stack_type inputStack) : stack이 비었는지 확인한다.
	*	int is_full(stack_type inputStack) : 스택이 꽉찼는지 확인한다.
	*	element pop(stack_type_ptr inputStack) : 스택의 나중의 넣었던 값을 지우고 반환한다.
*/
#define MAX_SIZE 20
#include <stdio.h>
typedef int element; //elemnet 는 char 과 같다.

typedef struct {
	element data[MAX_SIZE]; //element 타입으로 저장할 data 배열 선언
	int top;//몇번째 인덱스 까지 저장되어있는지 확인한다.
} stack_type;

typedef stack_type* stack_type_ptr; //stack_type 에 대한 포인터를 stack_type_ptr 로 정의한다.

void init(stack_type_ptr inputStack); //원본 stack 을 바꾸기 위해 stack_type_ptr 사용 (참조 호출)
void push(stack_type_ptr inputStack, element data); //원본 stack 을 바꾸기 위해 stack_type_ptr 사용 (참조 호출)
int is_empty(stack_type inputStack);//원본 stack 을 바꾸면 안되기 때문에 stack_type 사용 (값 호출)
int is_full(stack_type inputStack); //원본 stack 을 바꾸면 안되기 때문에 stack_type 사용 (값 호출)
element pop(stack_type_ptr inputStack);//원본 stack 을 바꾸기 위해 stack_type_ptr 사용 (참조 호출)
element peek(stack_type inputStack);//스택의 최상단 값을 확인하는 함수


int main() {
	stack_type s; //스택에 넣어야 뒤집어 나오므로 스택을 선언한다.
	init(&s);	//선언된 스택을 초기화한다.

	push(&s, 1); //s 스택에 1을 넣는다.
	push(&s, 2); //s 스택에 2를 넣는다.
	push(&s, 3); //s 스택에 3을 넣는다.
	printf("%d\n", pop(&s)); //s 스택의 최상단 값을 지우고 반환한다. 3dl 반환됨
	printf("%d\n", pop(&s)); //s 스택의 최상단 값을 지우고 반환한다. 2가 반환됨
	printf("%d\n", pop(&s));//s 스택의 최상단 값을 지우고 반환한다. 1이 반환됨
	printf("%d\n", pop(&s)); //더이상 저장된 값이 없으므로 오류가 발생한다.


}

void init(stack_type_ptr inputStack) {  //stack 구조체를 초기화한다. 
	inputStack->top = -1; //초기화는 top 을 - 1 로 한다.
}

void push(stack_type_ptr inputStack, element data) { //inputStack 에 data 를 넣는다.

	if (is_full(*inputStack)) { //is_full 은 call by value 이므로 inputStack 이 가르키는 값을 넣는다.
		//배열이 꽉찼으면 데이터를 밀어넣을수 없다.
		printf("더이상 데이터를 넣을 수 없습니다!");
		exit(1);
	}
	else {//배열이 꽉차지 않았으므로 데이터를 밀어넣는다.
		inputStack->top += 1;  //저장된 top 을 1 증가시키고
		inputStack->data[inputStack->top] = data; //그 top 에 저장된 걸 index 로 사용하여 그 인덱스에 data 를 넣는다.
	}

}

int is_empty(stack_type inputStack) { // inputStack 이 비었는지 확인한다.
	return ((inputStack.top == -1)); //== 연산자를 사용해서 -1 이면 빈값이기때문에 1이 반환된다.
	//아니면 0이 반환된다.
}

int is_full(stack_type inputStack) { //inputStack 이 꽉찼는지 확인한다.

	return  (inputStack.top == (MAX_SIZE - 1)); //== 연산자를 사용해서 참이면 1이 반환된다.
	//그렇기때문에 꽉차면 1, 꽉차지 않으면 0이 반환된다.
}


element pop(stack_type_ptr inputStack) { //마지막 넣었던 값을 지우고 반환하는 함수다.

	if (is_empty(*inputStack)) {//is_empty 은 call by value 이므로 inputStack 이 가르키는 값을 넣는다.
		//is_empty 가 참 즉, top 이 -1 이면 더이상 지울수 없기 때문에 수행된다.
		printf("더이상 지울수 없습니다!");
		exit(1);
	}
	else {
		element returnData = inputStack->data[inputStack->top]; //inputStack->top 는 마지막 저장된 인덱스를 의미한다.
		//그 인덱스가 가진 값을 returnData 에 할당한다.
		inputStack->top -= 1; //데이터를 지울거므로  top 을 -1 한다

		return returnData; //그 후 아까 할당한 returnData 를 반환한다.
	}

}
element peek(stack_type inputStack) {
	if (is_empty(inputStack)) {
		printf("값이 없습니다!");
		exit(1);
	}
	return inputStack.data[inputStack.top];
}

