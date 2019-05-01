#include <stdio.h>
#include <stdlib.h>
#define MAX_QUE_SIZE 10
typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUE_SIZE];
} Circle_Que;

typedef  Circle_Que* Circle_Que_ptr;

void error(char *String) {
	printf("%s", String);
	exit(1);
}
void init(Circle_Que_ptr q){
	q->front = 0;
	q->rear = 0;
}

int is_empty(Circle_Que_ptr q) {
	return q->front == q->rear;
}
int is_full(Circle_Que_ptr q) {
	return (q->rear + 1) % MAX_QUE_SIZE == q->front;

	
}
element deque(Circle_Que_ptr q) {
	if (is_empty(q)) {
		error("큐가 비었습니다!");
	}
	q->front = (q->front + 1) % MAX_QUE_SIZE;
	return q->data[q->front];
}
void enque(Circle_Que_ptr q, element data) {
	if (is_full(q)) {
		error("큐가 가득 찼습니다.");
	}
	q->rear = (q->rear + 1) % MAX_QUE_SIZE;
	q->data[q->rear] = data;
}
void display(Circle_Que_ptr q) {
	printf("원형 큐 (FRONT = %d, REAR = %d)    ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear) {
				break;
			}
		} while (i != q->front);
	}
	printf("\n");
}


int main() {
	Circle_Que a;
	Circle_Que_ptr q;
	q = &a;

	init(q);
	enque(q, 1);
	display(q);
	enque(q,2);
	display(q);
	deque(q);
	display(q);
	enque(q, 3);
	display(q);
	enque(q, 4);
	display(q);
	deque(q);
	display(q);
	enque(q, 5);
	display(q);
	enque(q, 6);
	display(q);
	

}

