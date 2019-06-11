#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct Link {
	element data;
	struct Link *next;
}Node;

typedef struct {
	int size;
	Node* top;
}stack;

void init(stack* st) {
	st->size = 0;
	st->top = NULL;
}

void push(stack* st,element data) {
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->data = data;
	temp->next = st->top;
	st->top = temp;
	st->size += 1;
}
int is_empty(stack* st) {
	return (st->top == NULL);
}

void printNode(Node *head) {
	Node *temp = head;
	while (temp != NULL) {
		printf("%d->", temp->data);
		temp = temp->next;
	}
}

element pop(stack* st) {
	if (is_empty(st)) {
		printf("스택이 비었음!");
		exit(0);
	}
	element data = st->top->data;
	st->size -= 1;
	Node *remove = st->top;
	st->top = st->top->next;
	free(remove);
	
	return data;
}

int main() {
	stack st;
	init(&st);
	for (int i = 0; i < 10; i++) {
		push(&st, i);
	}

	while (!is_empty(&st)) {
		printf("저장된 데이터 : %d, 길이 : %d\n", pop(&st),st.size);
	}

}
