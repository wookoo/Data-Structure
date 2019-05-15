#include <stdio.h>
#include <stdlib.h>

typedef int element;

struct linkedNum {
	element val;
	struct linkedNum *next;
};

typedef struct linkedNum ListNode;



void printNode(ListNode *node) {

	struct linkedNum *temp = node;
	while (temp != NULL)
	{
		printf("%d->", temp->val);
		temp = temp->next;
	}
	printf("NULL\n");
}

ListNode* insert_first(ListNode *head, element data) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->val = data;
	p->next = head;
	head = p;
	return head;
}

ListNode* insert(ListNode *head, ListNode *pre, element data) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->val = data;
	p->next = pre->next;
	pre->next = p;
	return head;
}
ListNode* delete_first(ListNode *head) {
	if (head == NULL) return NULL;
	ListNode *remove = head;
	head = head->next;
	free(remove);
	return head;
}
ListNode* delete(ListNode *head,ListNode *pre) {
	ListNode *remove = pre;
	pre = pre->next;
	free(pre);
	return head;
}


int main() {
	ListNode *head = (ListNode *)malloc(sizeof(ListNode));
	head = NULL;
	for (int i = 5; i > 0; i--) {
		head = insert_first(head, i);
		printNode(head);
	}
	for (int i = 5; i > 0; i--) {
		head = delete_first(head);
		printNode(head);
	}
	
	
}
