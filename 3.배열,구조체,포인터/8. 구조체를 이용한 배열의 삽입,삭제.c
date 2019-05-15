#include <stdio.h>
#define MAX_LIST_SIZE 50

typedef int element;

typedef struct {
	element array[MAX_LIST_SIZE];
	int size;
}ArrayList;

typedef ArrayList* ArrayList_ptr;

void init(ArrayList_ptr arr) {
	arr->size = 0;
}
int is_full(ArrayList_ptr arr) {
	return arr->size == MAX_LIST_SIZE;
}

int is_empty(ArrayList_ptr arr) {
	return arr->size == 0;
}

void error(char* errorName) {
	printf("%s", errorName);
	exit(1);
}

void insert_last(ArrayList_ptr arr,element data) {
	
	if (is_full(arr)) {
		error("더이상 값을 넣을 수 없습니다");
	}
	arr->array[arr->size++] = data;
}

void delete_first(ArrayList_ptr arr) {
	if (is_empty(arr)) {
		error("값을 지울 수 없습니다");
	}
	for (int i = 1; i < arr->size; i++) {
		arr->array[i - 1] = arr->array[i];
		
	}
	arr->size--;

}
void delete_last(ArrayList_ptr arr) {
	if (is_empty(arr)) {
		error("값을 지울 수 없습니다");
	}
	arr->size--;
}


void insert(ArrayList_ptr arr, int index, element data) {
	if (is_full(arr)) {
		error("더이상 값을 넣을 수 없습니다");
	}
	for (int i = arr->size - 1; i >= index; i--) {
		arr->array[i + 1] = arr->array[i];
	}
	arr->array[index] = data;
	arr->size++;
}

void delete(ArrayList_ptr arr, int index) {
	if (is_empty(arr)) {
		error("더이상 값을 넣을 수 없습니다.");
	}
	for (int i = index; i < arr->size; i++) {
		arr->array[i] = arr->array[i + 1];
	}
	arr->size--;
}
void printList(ArrayList_ptr arr) {
	for (int i = 0; i < arr->size; i++) {
		printf("%d ", arr->array[i]);
	}
	printf("\tSize = %d", arr->size);
	printf("\n");
	
}
int main() {
	ArrayList list;
	init(&list);
	printList(&list);
	insert_last(&list, 10);
	printList(&list);
	insert_last(&list, 20);
	printList(&list);
	insert_last(&list, 30);
	printList(&list);
	insert(&list, 1, 40);
	printList(&list);
	insert(&list, 2, 50);
	printList(&list);
	delete(&list, 3);
	printList(&list);
	delete_first(&list);
	printList(&list);
	delete_last(&list);
	printList(&list);
}
