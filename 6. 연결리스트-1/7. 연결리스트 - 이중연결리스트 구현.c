

#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DList {
	element data;
	struct DList* rlink;
	struct DList* llink;
}DNode;

void init(DNode *node) {
	node->llink = node->rlink = node;
}

void printNode(DNode *node) {
	DNode *temp = node->rlink;

	while (temp != node) {
		printf(" <-|%d|-> ", temp->data);
		temp = temp->rlink;
	
	}
/*
	for (temp = temp->rlink; temp != node; temp = temp->rlink)
	{
		printf(" <-|%d|-> ", temp->data);


	}*/
	printf("\n");
}
void dinsert(DNode *node,element data) {
	DNode *newNode = (DNode *)malloc(sizeof(DNode));

	newNode->data = data;
	newNode->llink = node;
	newNode->rlink = node->rlink;
	node->rlink->llink = newNode;
	node->rlink = newNode;
}
void ddelete(DNode *head, DNode *target) {
	if (target == head) {
		return;
	}
	target->llink->rlink = target->rlink;
	target->rlink->llink = target->llink;
	free(target);
}
int main() {
	DNode *newList = (DNode *)malloc(sizeof(DNode));
	init(newList);
	for (int i = 0; i < 10; i++) {
		dinsert(newList, i);
		printNode(newList);
	}
	for (int i = 0; i < 10; i++) {
	
		ddelete(newList, newList->rlink);
		printNode(newList);

	}
}
