/*
	* 문제 
	*	괄호쌍으로 된 문자열을 받아서 그 문자열이 올바른 괄호쌍인지 확인한다.
	
	* 출력
	*	올바른 괄호 쌍이면 parentheses are balanced 를 출력한다.
	*	올바르지 않은 괄호 쌍이면 parentheses are NOT balanced 를 출력한다.
	
	*알고리즘
	*	스택을 사용하여 구현을 한다. 
	*	스택이 비어있는 상태에서 ) 가 들어오면 그 배열은 NOT balanced 다.
	*	스택이 비어있지 않는 상태에서 ) 가 들어오면, ) 를 저장하지 않고, 마지막에 저장한 ( 를 삭제한다.
	*	문자열이 NULL 이 아닐때 까지 반복을 한다.
	
	*함수
	*	void init(stack_type_ptr inputStack) : stack 을 초기화한다.
	*	void push(stack_type_ptr inputStack, element data) : stack에 받아온 data 를 넣는다.
	*	int is_empty(stack_type inputStack) : stack이 비었는지 확인한다.
	*	int is_full(stack_type inputStack) : 스택이 꽉찼는지 확인한다.
	*	element pop(stack_type_ptr inputStack) : 스택의 나중의 넣었던 값을 지우고 반환한다.
	*	char get_symbol(char s[]) : 호출할때 마다 문자열 배열 s 의 0번째...1번째... n 번째 인덱스 값을 반환한다.
	*	int paren_test(char s[]) : balanced 한지 Not balanced 한지 확인한다.
*/
#define MAX_SIZE 20
#include <stdio.h>
typedef char element; //elemnet 는 char 과 같다.

typedef struct {
	element statck[MAX_SIZE]; //element 타입으로 저장할 statck 배열 선언
	int top;//몇번째 인덱스 까지 저장되어있는지 확인한다.
} stack_type;

typedef stack_type* stack_type_ptr; //stack_type 에 대한 포인터를 stack_type_ptr 로 정의한다.

void init(stack_type_ptr inputStack); //원본 stack 을 바꾸기 위해 stack_type_ptr 사용 (참조 호출)
void push(stack_type_ptr inputStack, element data); //원본 stack 을 바꾸기 위해 stack_type_ptr 사용 (참조 호출)
int is_empty(stack_type inputStack);//원본 stack 을 바꾸면 안되기 때문에 stack_type 사용 (값 호출)
int is_full(stack_type inputStack); //원본 stack 을 바꾸면 안되기 때문에 stack_type 사용 (값 호출)
element pop(stack_type_ptr inputStack);//원본 stack 을 바꾸기 위해 stack_type_ptr 사용 (참조 호출)
char get_symbol(char s[]);//호출할때 마다 문자열 배열 s 의 0번째...1번째... n 번째 인덱스 값을 반환한다.
int paren_test(char s[]);//balanced 한지 Not balanced 한지 확인한다.


int main() {


	char string[] = "()()(((()())))";
	int check = paren_test(string); //paren_test 에 "())()(((()())))" 넣은 결과값을 check 에 할당한다.
	if (check) //1이 반환되면 balanced 하다
	{
		printf("parentheses are balanced\n");
	}
	else { // 0이 반환되었으면 Not balanced 하다
		printf("parentheses are NOT balanced");
	}


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
		inputStack->statck[inputStack->top] = data; //그 top 에 저장된 걸 index 로 사용하여 그 인덱스에 data 를 넣는다.
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
		element returnData = inputStack->statck[inputStack->top]; //inputStack->top 는 마지막 저장된 인덱스를 의미한다.
		//그 인덱스가 가진 값을 returnData 에 할당한다.
		inputStack->top -= 1; //데이터를 지울거므로  top 을 -1 한다

		return returnData; //그 후 아까 할당한 returnData 를 반환한다.
	}

}


char get_symbol(char s[]) {
	static int index = 0; //함수가 호출될때마다 증가하기 위해 static 변수 사용한다.
	if (s[index] != NULL) {//만약 파라메터로 받아온 s 배열에 index 값이 NULL 이 아니면
		return s[index++]; //s의 index 값을 반환하고 index 는 1 증가한다.
	}
	else { //아니라면
		return NULL; //NULL 을 반환한다
	}
}

int paren_test(char s[]) {// balanced 한지 Not balanced 한지 확인하는 함수다.
	stack_type stack; //확인을 위해선 스택이 필요하기 때문에 스택을 생성한다.
	init(&stack); //생성한 스택을 초기화한다.
	char temp; //임시로 사용할 char 변수, while 문 컨트롤 및 if 문에 사용된다.
	int IsTrue = 1; //참 거짓을 판별하는 변수다. 초기값은 1 (참)으로 한다.
	while ((temp = get_symbol(s)) != NULL) { //temp 는 get_sybol 의 반환값인데, 그값이 NULL 이 아닐때 까지 반복
		if (is_empty(stack) == 1 && temp == ')') { //스택이 빈 상황인데 ) 가 들어가면 스택은 ) 꼴이 된다.
			IsTrue = 0;	//이는 곧 맞지 않은 괄호쌍을 의미하기에 false 로 만든다.
			break; //더이상 볼 가치가 없으므로 루프를 종료한다.
		}
		if (temp == ')') { //위의 if 문이 수행이 안되므로 해당 라인은 수행이된다.
			//들어온 값이 ) 경우
			pop(&stack); //스택엔 (....(( 꼴로 저장되어있기에 마지막 ( 를 지운다 
			//(....( 이런식으로 말이다.
		}
		else {
			push(&stack, temp); //아닐 경우 값이 ( 이 들어오는 경우기에 스택에 저장한다.
		}



	}
	return IsTrue; //참 거짓을 반환을 해준다.
}

