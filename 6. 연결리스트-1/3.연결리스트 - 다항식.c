#include <stdio.h>
#include <stdlib.h>

typedef int element;

struct linkedNum {
	int coef; //계수
	int expon; //지수
	struct linkedNum *next;
};

typedef struct linkedNum ListNode;

int is_empty(ListNode *node) {
	return node == NULL;
}


ListNode* insert_last(ListNode *head, element coef,element expon) {
	ListNode *last = head;
	while (last->next != NULL) {
		last = last->next;
	}
	ListNode *Node = (ListNode *)malloc(sizeof(ListNode));
	Node->next = NULL;
	Node->coef = coef;
	Node->expon = expon;
	last->next = Node;
	return head;
}

void printNode(ListNode *node) {

	struct linkedNum *temp = node;
	while (temp->next != NULL)
	{
		printf("%dX^%d+", temp->coef,temp->expon);
		temp = temp->next;
	}
	if (temp != NULL) {
		printf("%dX^%d", temp->coef, temp->expon);
	}
	printf("\n");
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
	ListNode *p;
	p = (ListNode *)malloc(sizeof(ListNode));
	p->coef = 3;
	p->expon = 12;
	p->next = NULL;
	printNode(p);
	p = insert_last(p, 2, 8);
	printNode(p);

	ListNode *q = (ListNode *)malloc(sizeof(ListNode));
	q->coef = 1;
	q->expon = 0;
	q->next = NULL;
	
	ListNode *last = p;
	while (last->next != NULL) {
		last = last->next;
	}
	last->next = q;
	printNode(p);
}
