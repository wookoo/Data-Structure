#include <stdio.h>
#include <stdlib.h>.


typedef int element;

struct linkedNum {
	element val;
	struct linkedNum *next;
};

typedef struct linkedNum ListNode;

int is_empty(ListNode *node) {
	return node == NULL;
}

void display(ListNode *node) {

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
	while (last != NULL && last->next != NULL) {
		last = last->next;
	}
	ListNode *Node = (ListNode *)malloc(sizeof(ListNode));
	Node->next = NULL;
	Node->val = data;
	if (head == NULL) {
		return Node;
	}
	last->next = Node;
	return head;
}


void gen_array(int *a, int data) {

	srand(time(NULL));
	for (int i = 0; i < data; i++) {
		a[i] = rand() % 101;
	}
}

void print_array(int *a ,int data) {
	for (int i = 0; i < data; i++) {
		printf("%d ", a[i]);
	}
	printf("\n\n");
}

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void quick_sort(int left, int right, int* a){
	int pivot = left;
	int j = pivot;
	int i = left + 1;
	if (left < right) {
		for (; i <= right; i++) {
			if (a[i] < a[pivot]) {
				j++;
				swap(&a[j], &a[i]);
			}
		}
		swap(&a[left], &a[j]);
		pivot = j;

		quick_sort(left, pivot - 1, a);
		quick_sort(pivot + 1, right, a);

	}
}

ListNode* gen_sortedList(int *a, int data) {
	/*
	for (int i = 0; i < data; i++) {
		for (int j = 0; j < data; j++) {
			if (a[i] < a[j]) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}*/

	quick_sort(0, data-1, a);
	ListNode *head = NULL;
	for (int i = 0; i < data; i++) {
		head = insert_last(head, a[i]);
	}


	return head;
}

int main() {
	int a[100];
	gen_array(a, 30);
	print_array(a, 30);
	ListNode *list;
	list = gen_sortedList(a, 30);
	display(list);

}
