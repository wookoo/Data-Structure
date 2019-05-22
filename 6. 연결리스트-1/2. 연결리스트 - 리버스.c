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
	if (is_empty(pre)) return NULL;
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->val = data;
	p->next = pre->next;
	pre->next = p;
	return head;
}
ListNode* delete_first(ListNode *head) {
	if (is_empty(head)) return NULL;
	ListNode *remove = head;
	head = head->next;
	free(remove);
	return head;
}
ListNode* delete(ListNode *head, ListNode *pre) {
	if (is_empty(pre)) return NULL;

	ListNode *remove = pre->next;
	pre->next = remove->next;
	free(remove);
	return head;
}

ListNode* delete_last(ListNode *head) {
	if (is_empty(head)) return NULL;
	ListNode *remove = head;
	ListNode *before = NULL;
	while (remove->next != NULL) {
		before = remove;
		remove = remove->next;

	}
	free(remove);
	before->next = NULL;
	return head;

}

ListNode* insert_last(ListNode *head, element data) {
	ListNode *last = head;
	while (last->next != NULL) {
		last = last->next;
	}
	ListNode *Node = (ListNode *)malloc(sizeof(ListNode));
	Node->next = NULL;
	Node->val = data;
	last->next = Node;
	return head;
}

ListNode* reverse(ListNode *head) {
	ListNode *q, *p, *r;
	p = head;
	q = NULL;
	while (p != NULL) {
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	return q;
}


int main() {
	ListNode *head;
	head = NULL;
	printNode(head);
	for (int i = 10; i < 31; i += 10) {
		head = insert_first(head, i);
		printNode(head);
	}

	head = insert(head, head, 40);
	printNode(head);
	head = insert(head, head, 50);
	printNode(head);
	head = delete_first(head);
	printNode(head);
	head = delete(head, head);
	printNode(head);
	head = insert_last(head, 60);
	printNode(head);
	head = insert_last(head, 70);
	printNode(head);
	head = delete_last(head);
	printNode(head);
	head = reverse(head);
	printNode(head);

}
