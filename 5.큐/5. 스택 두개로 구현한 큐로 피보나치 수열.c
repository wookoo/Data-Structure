#include <stdio.h>
#define MAX 100
typedef char elemant;

typedef struct { //스택 구조체를 정의하는 부분
	elemant data[MAX];
	int top;
}stack;

typedef stack* stack_ptr; //포인터를 좀더 쓰기 쉽게 stack_ptr 정의

typedef struct { //스택을 2개를 사용하는 큐 정의
	stack InputStack; //큐에는 스택이 2개가 있다.
	stack OutputStack;
} Queue;


//함수 원형을 정의하는 부분
typedef Queue* Queue_ptr;
void initStack(stack_ptr inputStack);
void initQueue(Queue_ptr q);
void enQueue(Queue_ptr q, elemant data);
elemant deQueue(Queue_ptr q);
int is_empty(stack inputStack);
int is_full(stack inputStack);
elemant peek(stack inputStack);
void push(stack_ptr inputStack, elemant data);
elemant pop(stack_ptr inputStack);
//함수 원형을 정의하는 부분 끝

int main() {
	for (int i = 0; i <= 10; i++) {
		printf("%d ", fibo(i)); //피보나치 수열의 10 번째 항까지 구한후 출력
	}
	return 0;
}

//-------------스택 관련 함수 정의하는 부분 시작----------------

//스택 초기화 함수, 구조체의 top 을 -1 로 설정
void initStack(stack_ptr inputStack) {
	inputStack->top = -1;
}


//스택이 비었나 검사하는 함수
int is_empty(stack inputStack) {
	return (inputStack.top == -1); //top 이 -1 이면 1 아니면 0 반환
}

//스택이 가득찼나 검사하는 함수
int is_full(stack inputStack) {
	return (inputStack.top == MAX - 1); //top 이 배열의 최대치면 1 아니면 0 반환
}

//스택의 최상단을 확인하는 함수 , 해당 프로그램에선 사용하지 않는 함수
elemant peek(stack inputStack) {
	if (is_empty(inputStack)) { //스택이 비었으면 return 할수 없으므로 프로그램 종료
		printf("peek 을 수행할수 없습니다.");
		exit();
	}
	return inputStack.data[inputStack.top]; //스택이 안비었으면 상단의 값 반환
}

//스택에 값을 넣는 함수
void push(stack_ptr inputStack, elemant data) {
	if (is_full(*inputStack)) { //스택이 가득찼으면 push 를 할수 없다.
		printf("push 를 수행 할 수 없습니다.");
		exit();
	}
	inputStack->data[++(inputStack->top)] = data; //스택이 가득차지 않았으면 top 을 1 증가후 값 삽입
}

//스택에 값을 제거하는 함수
elemant pop(stack_ptr inputStack) { //스택이 비었으면 pop 을 할수 없다
	if (is_empty(*inputStack)) {
		printf("더이상 pop 을 수행 할 수 없습니다");
		exit();
	}
	return inputStack->data[(inputStack->top)--]; //스택이 안비었으면 값을 반환후 top 을 1 감소시킨다.
}

//-------------스택 관련 함수 정의하는 부분 끝----------------


//------------큐 관련 함수 정의하는 부분 시작-------------------


//큐를 초기화 하는 함수
void initQueue(Queue_ptr q) { 

	//Queue 구조체에 존재하는 input outputStack 을 초기화 해준다.
	initStack(&q->InputStack);
	initStack(&q->OutputStack);
}

//큐에 데이터를 넣는 함수
void enQueue(Queue_ptr q, elemant data) {
	//큐에 데이터를 넣는 함수인데, 데이터는 inputStack 에 먼저 넣어야한다.
	// 1 2 3 을 넣었으면 1 2 3 이 출력되야 하므로
	//inputStack 엔 1 2 3 순으로 저장되어야 한다.
	push(&q->InputStack, data); //inputStack 에 값을 넣는다.
	//inputStack 이 full 인 경우의 동작은 push 에서 정해져있다.
}

//큐에서 데이터를 가져오는 함수
elemant deQueue(Queue_ptr q) {
	//OutputStack 이 비지 않았으면
	if (!is_empty(q->OutputStack)) {
		return pop(&q->OutputStack); //outPut 스택의 마지막으로 들어간 값을 반환한다.
	}
	else if (is_empty(q->InputStack)) { //만약 OutputStack 과 inputStack 둘다 비었으면
		printf("deQueue 를 수행할수 없습니다.");// deQueue 를 수행할수 없다
		exit();
	}
	else {//inputStack 이 안비었을때 경우
		while (!is_empty(q->InputStack)) {  //inputStack 이 빌때까지 수행
		
			//inputStack 에 있는 값을 outputStack 에 옮긴다.
			//즉 inputStack 이 1 2 3 으로 저장되어있고 OutputStack 이 값이 없으면
			// inputStack 은 값이 없어지고 OutputStack 은 3 2 1 이 된다
			// 즉 먼저 들어왔던 1 과 2 3 순으로 반환된다 >> 큐의 구조를 볼수 있다.
			push(&q->OutputStack, pop(&q->InputStack));
		}
		//옮긴게 끝났으면 OutputStack 의 최상단을 반환한다
		return pop(&q->OutputStack);
	}
}


//------------큐 관련 함수 정의하는 부분 끝-------------------

int fibo(int n) { //n 번째 항까지 구하는 피보나치 수열

	if (n == 0 || n == 1) { //피보나치 수열이 1이거나 0번쨰 항을 구하는 경우
		return n;  //그냥 n을 반환한다
	}
	//아래는 n 이 0 또는 0이 아닌 경우다
	Queue a; //큐를 생성해주고
	Queue_ptr q; //큐를 조금더 쉽게 ( & 를 쓰지 않기 위해) Queue_ptr 을 생성
	q = &a; //q 는 a 의 포인터

	initQueue(q); //q 를 초기화

	for (int i = 0; i <= n; i++) { //n 번쨰 항까지 계산해야 하므로
		if (i == 0 || i == 1) {
			enQueue(q, i); //i가 0과 1인 경우엔  큐에 0 또는 1을 넣는다.
	
		}
		else { //i 가 0 1 이 아닌 경우
			int first = deQueue(q); //전 전 항 > 1 2  이면 1 
			int second = deQueue(q);// 전항 > 1 2 이면 2 
			int temp = first + second; //피보나치는 전항과 2번쨰 전항을 더하는 것이다.
			enQueue(q, second); //second 가 이제 맨 앞의 수가 되고
			enQueue(q, temp); //temp 가 그 다음수가 된다
			
		}

	}
	deQueue(q); //for 문이 끝나면 큐엔 전항, 지금항 이 저장되어있으므로 전항을 지운다
	return deQueue(q); //지금항만 저장되어있으므로 그 값을 반환한다.

}
