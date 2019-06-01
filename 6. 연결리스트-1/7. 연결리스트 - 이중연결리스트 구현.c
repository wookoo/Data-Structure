#include <stdio.h>
#include <stdlib.h>
typedef int elemant;
typedef struct LinkedNum {
	int data;
	struct LinkedNum* prev;
	struct LinkedNum* next;
}Node;

Node* insert_last(Node* node,elemant data){
	Node *create = (Node *)malloc(sizeof(Node));
	create->next = NULL;
	create->prev = NULL;
	create->data = data;
	if (node == NULL) {
		return create;
	}
	Node *last = node;
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = create;
	create->prev = last;

	return node;
}
void print_node(Node* node) {
	Node* temp = node;
	while (temp != NULL) {
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL");
}


int main() {
	Node *head = NULL;
	head = insert_last(head, 5);
	head = insert_last(head, 9);
	print_node(head);
	return 0;
}
