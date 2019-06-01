#include <stdio.h>
#include <stdlib.h>
typedef int elemant;
typedef struct LinkedNum {
	int data;
	struct LinkedNum *prev;
	struct LinkedNum *next;
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
	printf("NULL\n");
}
Node* delete_first(Node* node) {
	if (node == NULL) {
		return node;
	}
	Node* remove = node;
	node = node->next;
	free(remove);
	return node;
}

Node* delete_node(Node* head, Node* prev) {
	if (head == NULL || prev == NULL) {
		return head;
	}
	Node* remove = prev->next;
	prev->next = remove->next;
	remove->next->prev = prev;
	free(remove);
	return head;
	//Node* temp = target->next;
	//temp->prev = target->prev;
}

Node* insert(Node* head, Node* prev, elemant data) {
	if (head == NULL || prev == NULL) {
		return head;
	}
	Node *create = (Node*)malloc(sizeof(Node));
	create->next = prev->next;
	create->prev = prev;
	create->data = data;
	prev->next = create;
	create->next->prev = create;
	return head;

}

int main() {
	Node *head = NULL;
	head = insert_last(head, 5);
	head = insert_last(head, 9);
	print_node(head);
	head = delete_first(head);
	print_node(head);
	head = insert(head,head,6);
	print_node(head);
	head = insert(head, head, 3);
	print_node(head);
	head = insert(head, head->next, 1);
	print_node(head);
	head = delete_node(head, head);
	
	print_node(head);
	return 0;
}
