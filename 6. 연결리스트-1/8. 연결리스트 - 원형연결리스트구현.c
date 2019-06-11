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

	if (node == NULL) return;

	ListNode* temp = node->next;
	do {
		
		printf("%d->", temp->val);
		temp = temp->next;

	} while (temp != node);
	printf("%d->", temp->val);
	printf("\n");

}

ListNode* insert_first(ListNode *head, element data) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->val = data;
	if (head == NULL) {
		node->next = node;
		return node;
	}
	node->next = head->next;
	head->next = node;
	
	return head;
}


ListNode* delete_first(ListNode *head) {
	if (head == head->next) {
		free(head);
		return NULL;
	}

	ListNode *remove = head->next;
	head->next = remove->next;
	free(remove);

	return head;
}




ListNode* insert_last(ListNode *head, element data) {
	
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->val = data;
	if (head == NULL) {
		node->next = node;
		return node;
	}
	node->next = head->next;
	head->next = node;
	head = node;
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
