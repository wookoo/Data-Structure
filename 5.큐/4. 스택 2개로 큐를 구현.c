#include <stdio.h>
#define MAX 100
#include <string.h>
typedef char elemant;
typedef struct {
	elemant data[MAX];
	int top;
}stack;
typedef stack* stack_ptr;

typedef struct {
	stack InputStack;
	stack OutputStack;
} Queue;

typedef Queue* Queue_ptr;
void init(stack_ptr inputStack);
void initQueue(Queue_ptr q);
void inQueue(Queue_ptr q, elemant data);
elemant deQueue(Queue_ptr q);
int is_empty(stack inputStack);
int is_full(stack inputStack);
elemant peek(stack inputStack);
void push(stack_ptr inputStack, elemant data);
elemant pop(stack_ptr inputStack);



void init(stack_ptr inputStack) {
	inputStack->top = -1;
}

void initQueue(Queue_ptr q) {
	init(&(q->InputStack));
	init(&(q->OutputStack));
}

void inQueue(Queue_ptr q, elemant data) {
	push(&q->InputStack, data);
}
elemant deQueue(Queue_ptr q) {
	if (!is_empty(q->OutputStack)) {
		return pop(&q->OutputStack);
	}
	else if (is_empty(q->InputStack)) {
		printf("deQueue 를 수행할수 없습니다.");
		exit();
	}
	else {
		while (!is_empty(q->InputStack)) {
			push(&q->OutputStack, pop(&q->InputStack));
		}
		return pop(&q->OutputStack);
	}
}

int is_empty(stack inputStack) {
	return (inputStack.top == -1);
}
int is_full(stack inputStack) {
	return (inputStack.top == MAX - 1);
}
elemant peek(stack inputStack) {
	if (is_empty(inputStack)) {
		printf("peek 을 수행할수 없습니다.");
		exit();
	}
	return inputStack.data[inputStack.top];
}
void push(stack_ptr inputStack, elemant data) {
	if (is_full(*inputStack)) {
		printf("push 를 수행 할 수 없습니다.");
		exit();
	}
	inputStack->data[++(inputStack->top)] = data;
}
elemant pop(stack_ptr inputStack) {
	if (is_empty(*inputStack)) {
		printf("더이상 pop 을 수행 할 수 없습니다");
		exit();
	}
	return inputStack->data[(inputStack->top)--];
}



int main() {
	Queue q;
	initQueue(&q);
	for (int i = 0; i < 5; i++) {
		inQueue(&q, i);
	}

	printf("%d\n", deQueue(&q));
	printf("%d", deQueue(&q));
}