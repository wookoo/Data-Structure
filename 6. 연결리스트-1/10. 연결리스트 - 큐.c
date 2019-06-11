#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct Link {
	element data;
	struct Link *next;
}Node;

typedef struct {
	int size;
	Node* front;
	Node* rear;
}que;

void init(que* q) {
	q->size = 0;
	q->front = q->rear = NULL;
}
int is_empty(que* q) {
	return (q->front == NULL);
}

void enque(que* q,element data) {
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;
	q->size += 1;
	if (is_empty(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		q->rear->next = temp;
		q->rear = temp;
	}
}




element deque(que* q) {
	if (is_empty(q)) {
		printf("큐가 비었습니다.");
		exit(0);
	}
	Node *temp = q->front;
	element data = q->front->data;
	q->front = q->front->next;
	free(temp);
	q->size -= 1;
	return data;
}

int main() {
	que q;
	init(&q);
	for (int i = 0; i < 10; i++) {
		enque(&q, i);
	}

	while (!is_empty(&q)) {
		printf("저장된 데이터 : %d, 길이 : %d\n", deque(&q),q.size);
	}
	printf("저장된 데이터 : %d, 길이 : %d\n", deque(&q), q.size);


}
