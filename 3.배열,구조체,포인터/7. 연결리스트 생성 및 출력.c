#include <stdio.h>
#include <stdlib.h>
struct linkedNum{
	int val;
	struct linkedNum *next;
};

void printNode(struct linkedNum *node) {

	struct linkedNum *temp = node->next;    
	while (temp != NULL)               
	{
		printf("%d\n", temp->val);    
		temp = temp->next;          
	}
}

int main() {
	struct linkedNum *first;
	struct linkedNum *node1, *node2, *node3;
	first = (struct linkedNum *)malloc(sizeof(struct linkedNum));
	first->val = NULL;
	node1 = (struct linkedNum *)malloc(sizeof(struct linkedNum));
	first->next = node1;
	node1->val = 10;
	node2 = (struct linkedNum *)malloc(sizeof(struct linkedNum));
	node1->next = node2;
	node2->val = 20;
	node3 = (struct linkedNum *)malloc(sizeof(struct linkedNum));
	node2->next = node3;
	node3->val = 30;
	node3->next = NULL;
	printNode(first);
}
