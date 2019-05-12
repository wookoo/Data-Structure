#include <stdio.h>
#include <stdlib.h>
#define MAX_QUE_SIZE 10
typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUE_SIZE];
} Que;

typedef  Que* Que_ptr;

void error(char *String) {
	printf("%s", String);
	exit(1);
}
void init(Que_ptr q){
	q->front = -1;
	q->rear = -1;
}

int is_empty(Que_ptr q) {
	return q->front == q->rear;
}
int is_full(Que_ptr q) {
	return q->rear == (MAX_QUE_SIZE - 1);
}
element deque(Que_ptr q) {
	if (is_empty(q)) {
		error("큐가 비었습니다!");
	}
	return q->data[++(q->front)];
}
void enque(Que_ptr q, element data) {
	if (is_full(q)) {
		error("큐가 가득 찼습니다.");
	}
	q->data[++(q->rear)] = data;
}

int main() {
	Que q;
	init(&q);
	for (int i = 0; i < 8; i++) {
		enque(&q, i);
	}
	while (!is_empty(&q)) {
		printf("%d", deque(&q));
	}
}

