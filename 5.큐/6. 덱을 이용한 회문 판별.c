#include <stdio.h>
#include <stdlib.h>
#define MAX_QUE_SIZE 10
typedef int element;
typedef struct { //원형 큐가 가지는 front rear 필드
	int front;
	int rear;
	element data[MAX_QUE_SIZE]; //데이터를 저장하는 배열
} Deque;

typedef  Deque* Deque_ptr;

//함수 원형 정의 부 시작
void error(char *String);
void init(Deque_ptr dq);
int is_empty(Deque_ptr dq);
int is_full(Deque_ptr dq);
element delete_front(Deque_ptr dq);
void add_rear(Deque_ptr dq, element data);
void add_front(Deque_ptr dq, element data);
element delete_rear(Deque_ptr dq);
char get_symbol(char *String);

//함수 원형 정의부 끝

int main() {
	Deque a;
	Deque_ptr dq = &a;
	init(dq);
	char String[] = "abcba";
	char sym;
	int IsTrue = 1; //String 이 참인지 거짓인지 확인하기 위한 변수
	while ((sym = get_symbol(String)) != NULL) {
		add_rear(dq, sym); //String 의 모든 요소를 덱에 삽입
	}
	while (!is_empty(dq)) { //덱이 비지 않을때 까지 반복
		char front;
		front = delete_front(dq); //일단 값이 무조건 존재 하므로 전면에서 값을 가져온다

		if (!is_empty(dq)) { //문자열이 짝수인 경우
			char rear;
			rear = delete_rear(dq); //후면에서 값을 가져온다
			if (rear != front) { //전면부와 후면부 즉, 처음값과 마지막 값이 같지 않으면
				IsTrue = 0; //그것은 회문이 아니기에 0으로 만들고
				break; //while 문종료
			}
		}
	}

	if (IsTrue) { //회문인 경우와 회문이 아닌 경우를 출력
		printf("회문");
	}
	else {
		printf("회문 아님");
	}

	return 0; //메인함수 종료

}


void error(char *String) { //오류 출력 함수
	printf("%s", String); //입력받은 오류를 출력하고 프로그램 종료
	exit(1);
}
void init(Deque_ptr dq) { //덱을 초기화, front 와 rear 을 0으로 바꿈
	dq->front = 0;
	dq->rear = 0;
}

int is_empty(Deque_ptr dq) { //덱이 빈 경우는 front 와 rear 가 같은 경우다
	return dq->front == dq->rear;
}
int is_full(Deque_ptr dq) { //덱이 가득 찬 경우는 rear 에서 1을 더한 값이 front 와 같은경우
	return (dq->rear + 1) % MAX_QUE_SIZE == dq->front;


}

element delete_front(Deque_ptr dq) { //덱의 앞에서 값을 지우는 경우
	if (is_empty(dq)) {
		error("덱이 비었습니다!");
	}
	//덱이 가득 비지 않았으면
	dq->front = (dq->front + 1) % MAX_QUE_SIZE; //시계방향으로 덱을 돌리고
	return dq->data[dq->front]; //값을 반환
}

void add_rear(Deque_ptr dq, element data) {
	if (is_full(dq)) {
		error("덱이 가득 찼습니다."); 
	}
	//덱이 가득차지  않았으면
	dq->rear = (dq->rear + 1) % MAX_QUE_SIZE; //시계방향으로 덱을 돌리고
	dq->data[dq->rear] = data; //값을 삽입
}

void add_front(Deque_ptr dq, element data) {
	if (is_full(dq)) { 
		error("덱이 가득 찼습니다.");
	}
	//덱이 가득 차지 않았으면
	dq->data[dq->front] = data; //값을 삽입하고
	dq->front = (dq->front - 1 + MAX_QUE_SIZE) % MAX_QUE_SIZE; //시계 반대방향으로 덱을 돌림
	
}

element delete_rear(Deque_ptr dq) {
	if (is_empty(dq)) { 
		error("덱이 비었습니다!");
	}
	//덱이 비지 않았으면
	element item = dq->data[dq->rear]; //값을 가져오고
	dq->rear = (dq->rear - 1 + MAX_QUE_SIZE) % MAX_QUE_SIZE; //시계 반대방향으로 덱을 돌리고
	return item; //값을 반환
}
char get_symbol(char *String) { //for strlen(String) 과 비슷함
	static int index = 0; //static 변수 선언, 함수 call 마다 1 씩 increase
	if (String[index] != NULL) { //NULL 값이 아니면
		return String[index++]; //반환후 index 1 증가
	}
	else
	{
		return NULL;
	}
}

