
#include <stdio.h>
#include <stdlib.h>

typedef int element;

struct linkedNum {
	element val;
	struct linkedNum *next;
};

typedef struct linkedNum ListNode;

int is_empty(ListNode *node) {
	return node == NULL;
}

void printNode(ListNode *node) {

	ListNode* temp = node;
	do {
		if (node == NULL) return;
		printf("%d->", temp->val);
		temp = temp->next;

	} while (temp != node);
	printf("\n");

}

ListNode* insert_first(ListNode *head, element data) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->val = data;
	p->next = head;
	if (head == NULL) {
		p->next = p;
		return p;
	}
	ListNode *last = head;
	
	while (last->next != head) {
		last = last->next;
	}

	head = p;
	last->next = p;
	return head;
}


ListNode* delete_first(ListNode *head) {
	ListNode *remove = head;
	if (head == NULL) return NULL;
	head = head->next;
	ListNode *last = head;

	while (last->next != remove) {
		last = last->next;
	}
	last->next = head;
	free(remove);
	return head;
}




ListNode* insert_last(ListNode *head, element data) {
	ListNode *last = head;

	while (last->next != head) {
		last = last->next;
	}
	ListNode *Node = (ListNode *)malloc(sizeof(ListNode));
	Node->next = head;
	Node->val = data;
	last->next = Node;
	return head;
}



int main() {
	ListNode *head = (ListNode *)malloc(sizeof(ListNode));
	head->next = head;
	head->val = 5;
	head = insert_first(head, 6);
	printNode(head);

	ListNode *list = NULL;
	list = insert_first(list, 10);
	list = insert_first(list, 20);
	list = insert_first(list, 30);
	list = insert_last(list, 40);
	list = insert_last(list, 50);
	list = delete_first(list);
	printNode(list);
}
