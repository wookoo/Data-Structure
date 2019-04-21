#include <stdio.h>
void insertValue(int* list, int loc, int value, int *items) {
	for (int i = *items; i >= loc; i--) {
		list[i + 1] = list[i];
	}
	list[loc] = value;
	*items += 1;
}

void deleteValue(int* list, int loc,int *items) {
	for (int i = loc; i <* items; i++) {
		list[i] = list[i + 1];
	}
	*items -= 1;
}
void printList(int *list, int items) {
	for (int i = 0; i < items; i++) {
		printf("%d ",list[i]);
	}
}
int main() {
	int a[10] = {1, 2, 3, 4, 5};
	int aIndex = 5;
	deleteValue(a, 2, &aIndex);
	printList(a, aIndex);
	printf("\n-----------------\n");
	insertValue(a, 3,9, &aIndex);
	printList(a, aIndex);
}
