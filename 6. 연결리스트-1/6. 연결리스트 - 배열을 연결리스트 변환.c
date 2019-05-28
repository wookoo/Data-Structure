#include <stdio.h>
#include <stdlib.h>.


typedef int element;

struct linkedNum {
	element val;
	struct linkedNum *next;
};

typedef struct linkedNum ListNode;

int is_empty(ListNode *list) {
	return (list == NULL);
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



ListNode* insert_last(ListNode *head, element data) {
	ListNode *last = head;
	while (last != NULL && last->next != NULL) { //last 와 last 의 next 가 비어있지 않으면
		last = last->next; //라스트 노드를 오른쪽으로 옮긴다
	}
	ListNode *Node = (ListNode *)malloc(sizeof(ListNode));
	Node->next = NULL;
	Node->val = data;
	if (is_empty(head)) { //헤드 노드가 비어있으면 생성된 Node 반환
		return Node;
	}
	last->next = Node; //헤드 노드가 비어있지 않으면 Node 의 
	return head;
}


void gen_array(int *a, int data) {

	srand(time(NULL));
	for (int i = 0; i < data; i++) {
		a[i] = abs(i - data);
	}
}

void print_array(int *a, int data) {
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

void quick_sort(int left, int right, int* a) {
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

	quick_sort(0, data - 1, a);
	ListNode *head = NULL;
	for (int i = 0; i < data; i++) {
		head = insert_last(head, a[i]);
	}


	return head;
}


int is_empty(ListNode *list) {
	return list == NULL; //리스트가 NULL 이면 1 NULL 이 아니면 0 반환
}

ListNode* delete(ListNode *list, element item) {



	if (list != NULL && list->val == item) { //처음 노드가 NULL 이 아니고 , 처음 노드가 item 일때
		ListNode *remove = list; //지울 노드는 처음 노드
		ListNode *result = list->next; //반환될 노드는 처음 노드의 다음 노드
		free(remove); //처음 노드를 지우고
		return result; //반환될 노드를 반환한다
	}
	else if (is_empty(list)) { //list 가 비어있으면 지울수 없으므로
		return NULL; //NULL 반환
	}
	ListNode *remove = list;
	ListNode *before = NULL;
	while (remove != NULL && remove->val != item) {
		
	   before = remove;
	   remove = remove->next;
	}
	
	if (before != NULL && remove != NULL && remove->val == item) {
		before->next = remove->next;
		free(remove);
	}
	else if (is_empty(remove->next) && remove->val == item) {
		return NULL;
	}

	return list;

}


ListNode* clear_list(ListNode *list) { //노드를 초기화 하는 함수
	ListNode *remove = list; //지울 노드
	ListNode *temp = list; //노드를 임시로 저장
	while (temp != NULL) { //임시 노드가 NULL 이 아닐때 까지 반복
		temp = temp->next; //임시 노드는 옆으로 이동한다
		free(remove); // 이동하기 전의 임시노드는 지워야 하므로 free 
		remove = temp; //지울 노드는 다음 노드가 된다.
	}
	// 1 2 3 4 면, 2 3 4 , 3 4, 4, 5 순이 된다
	return NULL; //해당 작업이 끝나면 NULL 이 반환된다.
}
int is_in_list(ListNode *list,element data) { //해당 데이터가 배열 안에 있는지 검사하는 항목
	if (is_empty(list)) { //list 가 비어있으면 무조건 없으므로
		return 0; //0을 반환한다
	}
	//list 가 NULL 이 아닌 경우 아래들이 수행됨
	ListNode *temp = list; //ListNode 포인터를 담는 temp 변수에 list 를 할당
	while (temp != NULL) { //temp 가 비어있지 않을때 까지 반복한다
		if (temp->val == data) { //temp 가 가진 val 필드가 data 와 같은 경우
			return 1; //값이 있으므로 1 이 반환되고 함수 끝
		}
		temp = temp->next; //1이 반환되지 않았으면 temp 는 옆 노드로 옮겨간다
	}
	return 0; //while 문에서 return 1 이 수행되지 않았으면 값이 없으므로 0 반환

}
int get_length(ListNode *list) { //연결리스트의 길이를 구하는 get__length 함수
	if (is_empty(list)) { //들어온 리스트가 아무것도 없으면
		return 0; // 길이를 0으로 반환해준다
	}
	//아래 부분은 매개변수인 list 가 NULL 이 아닌 경우 수행된다
	int size = 0; //길이는 일단 0으로 한다
	ListNode *temp = list; //ListNode 포인터를 담는 temp 변수에 list 를 할당한다
	while (temp != NULL) { //temp 가 NULL 이 아닐때 까지 반복한다
		temp = temp->next; //temp 는 다음 노드로 이동시키고
		size++; //사이즈를 1 증가시킨다
	}
	return size; //while 문이 끝난 후 size 가 반환이된다.
}
int is_full(ListNode *list) {  //연결리스트의 포화 검사 함수
	ListNode *t = (ListNode *)malloc(sizeof(ListNode));//동적 할당을 해본다
	int temp = (t == NULL); //동적 할당의 결과를 temp 에 넣고
	free(t); //생성된 t 를 Free 처리 한다.
	return temp; //동적 할당에 실패하면 1, 성공하면 0이 반환된다
}
ListNode* add(ListNode *list, element item) {

}

//add list,item
//delete list item
//clear list
//is in list
//get_length
//is_empty
//is_full


int main() {
	int a[100];
	gen_array(a, 30);
	print_array(a, 30);
	ListNode *list;
	list = gen_sortedList(a, 30);
	display(list);
	ListNode *temp = list;
	list = clear_list(list);
	display(list);
	display(temp);
	printf("%d\n", is_in_list(list, 5));
	
	printf("%d", get_length(list));
	

}
