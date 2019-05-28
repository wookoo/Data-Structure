
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


ListNode* insert_last(ListNode *head, element coef, element expon) {
	ListNode *last = head;
	while (last != NULL && last->next != NULL) {
		last = last->next;
	}
	ListNode *Node = (ListNode *)malloc(sizeof(ListNode));
	Node->next = NULL;
	Node->coef = coef;
	Node->expon = expon;

	if (head == NULL) {
		return Node;
	}
	last->next = Node;
	return head;
}
ListNode* AddPoly(ListNode *first, ListNode *second) {
	ListNode *firstTemp, *secondTemp;
	firstTemp = first;
	secondTemp = second;
	ListNode *result = NULL;

	while (firstTemp != NULL && secondTemp != NULL) {
		if (firstTemp->expon == secondTemp->expon) {
			//덧셈 연산
			result = insert_last(result, firstTemp->coef + secondTemp->coef, firstTemp->expon);

			firstTemp = firstTemp->next;
			secondTemp = secondTemp->next;


		}
		else if (firstTemp->expon > secondTemp->expon) {
			result = insert_last(result, firstTemp->coef, firstTemp->expon);
			firstTemp = firstTemp->next;

		}
		else {
			result = insert_last(result, secondTemp->coef, secondTemp->expon);
			secondTemp = secondTemp->next;
		}


	}
	while (firstTemp != NULL) {
		result = insert_last(result, firstTemp->coef, firstTemp->expon);
		firstTemp = firstTemp->next;
	}
	while (secondTemp != NULL) {
		result = insert_last(result, secondTemp->coef, secondTemp->expon);
		secondTemp = secondTemp->next;
	}


	return result;

}




void printNode(ListNode *node) {

	struct linkedNum *temp = node;
	int first = 1;
	while (temp->next != NULL)
	{
		if (first) {
			printf("%dX^%d", temp->coef, temp->expon);
			first = 0;
		}
		else {
			printf("%+dX^%d", temp->coef, temp->expon);
		}
		
		temp = temp->next;
	}
	if (temp != NULL && temp->expon != 0) {
		if (first) {
			printf("%dX^%d", temp->coef, temp->expon);
			first = 0;
		}
		else {
			printf("%+dX^%d", temp->coef, temp->expon);
		}
		
	}
	else if (temp->expon == 0) {
		if (first) {
			printf("%d", temp->coef);
			first = 0;
		}
		else {
			printf("%+d", temp->coef);
		}
		
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
	//	printNode(p);

	p = insert_last(p, 2, 8);
	//printNode(p);

	p = insert_last(p, 1, 0);
	printNode(p);

	ListNode *q;
	q = NULL;
	q = insert_last(q, 8, 12);
	q = insert_last(q, -3, 10);
	q = insert_last(q, 10, 6);
	printNode(q);

	ListNode *result = AddPoly(p, q);
	printNode(result);


}
