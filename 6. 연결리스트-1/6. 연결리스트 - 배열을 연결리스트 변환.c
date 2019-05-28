#include <stdio.h>
#include <stdlib.h>.


typedef int element;

struct linkedNum {
	element val;
	struct linkedNum *next;
};

typedef struct linkedNum ListNode;


int is_in_list(ListNode *list, element data); //노드 안에 값이 있나 검사하는 함수 원형 정의
int is_empty(ListNode *list); //노드가 비었나 검사하는 함수 원형 정의
void display(ListNode *list); //노드를 출력하는 함수 원형 정의
ListNode* insert_last(ListNode *list, element data); //마지막에 값을 노드를 추가하는 함수 원형 정의
void gen_array(int *a, int data); //랜덤한 수를 생성하는 함수 원형 정의
void print_array(int *arr, int size); //배열을 출력하는 함수 원형 정의
void swap(int *a, int *b); //스왑 함수 원형 정의
void quick_sort(int left, int right, int* a); //퀵정렬 함수 원형 정의
ListNode* gen_sortedList(int *a, int data); //정렬된 연결리스트를 반환하는 함수 원형 정의
ListNode* delete(ListNode *list, element item); //연결리스트에서 값을 지우는 함수 원형 정의
ListNode* clear(ListNode *list); //연결리스트를 초기화 하는 함수 원형 정의
int get_length(ListNode *list); //연결 리스트의 길이를 구하는 함수 원형 정의
int is_full(ListNode *list);  //연결리스트의 포화 검사 함수 원형 정의
ListNode* add(ListNode *list, element item); //정렬된 연결리스트의 값을 추가하는 함수 원형 정의


int main() {
	int a[100]; //배열 선언
	gen_array(a, 30); //배열의 30개 요소만큼 랜덤값을 추가한다
	print_array(a, 30); //잘 추가되었나 출력하고
	ListNode *list = NULL; //동적 연결리스트 생성
	list = gen_sortedList(a, 30); //a 배열을 정렬하고 연결리스트로 만든다
	display(list); //정상적으로 추가 됬나 출력



	printf("연결리스트에서 -7 3번 추가\n");
	for (int i = 0; i < 3; i++) {
		list = add(list, -7); //연결리스트에 -7 이라는 값을 정렬된 상태로 추가한다
	}

	display(list); //-7 이 잘 들어갔는지 출력한다

	list = delete(list, -7); //리스트에서 -7라는 숫자 몽땅 지운다.
	printf("연결리스트에서 -7 삭제\n");
	display(list); //연결리스트에서 -7가 삭제됬는지 출력
	list = clear(list);
	printf("연결리스트클리어\n");
	display(list);



}



int is_in_list(ListNode *list, element data) { //해당 데이터가 배열 안에 있는지 검사하는 항목
	if (is_empty(list)) { //list 가 비어있으면 무조건 없으므로
		return 0; //0을 반환한다
	}
	//list 가 NULL 이 아닌 경우 아래들이 수행됨
	ListNode *temp = list; //ListNode 포인터를 담는 temp 변수에 list 를 할당
	while (!is_empty(temp)) { //temp 가 비어있지 않을때 까지 반복한다
		if (temp->val == data) { //temp 가 가진 val 필드가 data 와 같은 경우
			return 1; //값이 있으므로 1 이 반환되고 함수 끝
		}
		temp = temp->next; //1이 반환되지 않았으면 temp 는 옆 노드로 옮겨간다
	}
	return 0; //while 문에서 return 1 이 수행되지 않았으면 값이 없으므로 0 반환

}

int is_empty(ListNode *list) {
	return (list == NULL); //리스트가 NULL 이면 1 NULL 이 아니면 0 반환
}

void display(ListNode *list) { //연결리스트를 출력하는 함수

	ListNode *temp = list; //임시배열 temp 선언
	while (!is_empty(temp)) //temp  가 비어있지 않을때까지
	{
		printf("%d->", temp->val); //temp 가 가진 값 출력
		temp = temp->next; //temp 를 옆 노드로 민다
	}
	printf("NULL\n");
}



ListNode* insert_last(ListNode *list, element data) {
	ListNode *last = list;
	while (!is_empty(last) && !is_empty(last->next)) { //last 와 last 의 next 가 비어있지 않으면
		last = last->next; //라스트 노드를 오른쪽으로 옮긴다
	}
	ListNode *Node = (ListNode *)malloc(sizeof(ListNode));
	Node->next = NULL;
	Node->val = data;
	if (is_empty(list)) { //헤드 노드가 비어있으면 생성된 Node 반환
		return Node;
	}
	last->next = Node; //헤드 노드가 비어있지 않으면 마지막 노드에 생성된 노드를 붙임
	return list;
}


void gen_array(int *a, int data) {

	srand(time(NULL)); //랜덤 시드 초기화
	for (int i = 0; i < data; i++) {

		a[i] = rand() % 101;  //a 의 i 번째 인덱스 랜덤 값 할당
	}
}

void print_array(int *arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");
}

void swap(int *a, int *b) { //변수 두개의 자리를 교환 하는 함수
	int t = *a; //t 는 a 가 가르키는 값 저장
	*a = *b; //a 가 가르키는 값은 b 가 가르키는 값 저장
	*b = t; //b 가 가르키는 값은 t 가 갖는 값 저장
}

//퀵 소트 : 분할정복으로써 피벗을 하나 잡고 피벗의 왼쪽은 모든 피벗보다 작은수 오른쪽은 피벗보다 큰 수를 둔다.
//bestCase 에서 NlogN 의 시간복잡도를 갖는다
void quick_sort(int left, int right, int* a) { //퀵정렬, 인자로는 왼쪽값 오른쪽값, 배열 a 
	int pivot = left; //비교 대상인 피벗을 left 로 잡는다
	int j = pivot; //교체대상, j 는 피벗과 같이 설정한다.
	int i = left + 1; //비교 할 값,
	if (left < right) { //피벗 앞에는 피벗보다 작은 모든 원소가 와야 한다
		for (; i <= right; i++) {
			if (a[i] < a[pivot]) { //만약 a 의 i 번째 인덱스가 피벗보다 크면
				j++; //j 를 옆인덱스로 옮기고
				swap(&a[j], &a[i]); //a 와 j 의 값을 바꾼다
			}
		}
		swap(&a[left], &a[j]); //i 위치가 right 랑 같아지면 비교가 끝난것이므로 left 와 j 의 값을 스왑하고 
		pivot = j; //피봇을 재설정한다

		quick_sort(left, pivot - 1, a); //그 후 재귀로 퀵소트를 호출한다
		quick_sort(pivot + 1, right, a);

	}
}

ListNode* gen_sortedList(int *a, int data) {

	quick_sort(0, data - 1, a);
	ListNode *head = NULL; //반환할 노드를 생성 하고
	for (int i = 0; i < data; i++) {
		head = insert_last(head, a[i]); //반환할 노드 마지막에 정렬된 a 배열을 하나 하나 가져와서 노드를 생성하고
		//생성된 노드를 맨 뒤에 붙인다
	}


	return head;
}


ListNode* delete(ListNode *list, element item) {

	do { //do while 문을 사용하여 1번이상 무조건 수행하게 한다

		if (!is_empty(list) && list->val == item) { //처음 노드가 비지 않았고 , 처음 노드가 item 일때
			ListNode *remove = list; //지울 노드는 처음 노드
			ListNode *result = list->next; //반환될 노드는 처음 노드의 다음 노드
			list = result;
			free(remove); //처음 노드를 지우고

			//return result; //반환될 노드를 반환한다
		}
		else if (is_empty(list)) { //list 가 비어있으면 지울수 없으므로
			return NULL; //NULL 반환
		}
		ListNode *remove = list; //지울 노드는 기본값으로 처음 노드
		ListNode *before = NULL; //지울노드의 이전 노드
		while (!is_empty(remove) && remove->val != item) {
			//remove 가 비지 않고, remove 가 val 이 item 이 아니면
			before = remove;
			remove = remove->next; //다음 노드를 탐색한다
		}

		if (!is_empty(before) && !is_empty(remove) && remove->val == item) {
			//이전노드가 비지 않았고, 현재 노드도 비지 않았는데, 현재 노드가 item 을 가지면
			before->next = remove->next; //이전노드는 현재 노드의 다음을 가르키게 한다
			// 1 2 3 이면 1 (2) 3 꼴
			free(remove); //현재 노드를 free 로 반환한다.
		}
		else if (!is_empty(remove) && remove->val == item && !is_empty(remove->next)) {
			//현재노드가 비지 않았고, 다음노드도 비지 않았고, 현재 노드가 item 과 같으면
			list = remove->next; //list 는remove 의 옆노드로 간다
			free(remove); //현재 노드 free
		}

	} while (is_in_list(list, item)); //입력받은 item 이 입력받은 list 에 없을때 까지 반복한다
	return list; //변경된 list 반환

}


ListNode* clear(ListNode *list) { //노드를 초기화 하는 함수
	ListNode *remove = list; //지울 노드
	ListNode *temp = list; //노드를 임시로 저장
	while (!is_empty(temp)) { //임시 노드가 비지 않을때 까지 반복
		temp = temp->next; //임시 노드는 옆으로 이동한다
		free(remove); // 이동하기 전의 임시노드는 지워야 하므로 free 
		remove = temp; //지울 노드는 다음 노드가 된다.
	}
	// 1 2 3 4 면, 2 3 4 , 3 4, 4, 5 순이 된다
	return NULL; //해당 작업이 끝나면 NULL 이 반환된다.
}

int get_length(ListNode *list) { //연결리스트의 길이를 구하는 get__length 함수
	if (is_empty(list)) { //들어온 리스트가 아무것도 없으면
		return 0; // 길이를 0으로 반환해준다
	}
	//아래 부분은 매개변수인 list 가 NULL 이 아닌 경우 수행된다
	int size = 0; //길이는 일단 0으로 한다
	ListNode *temp = list; //ListNode 포인터를 담는 temp 변수에 list 를 할당한다
	while (!is_empty(temp)) { //temp 가 비지 않았을때까지 반복
		temp = temp->next; //temp 는 다음 노드로 이동시키고
		size++; //사이즈를 1 증가시킨다
	}
	return size; //while 문이 끝난 후 size 가 반환이된다.
}
int is_full(ListNode *list) {  //연결리스트의 포화 검사 함수
	ListNode *t = (ListNode *)malloc(sizeof(ListNode));//동적 할당을 해본다
	int temp = is_empty; //동적 할당의 결과를 temp 에 넣고
	free(t); //생성된 t 를 Free 처리 한다.
	return temp; //동적 할당에 실패하면 1, 성공하면 0이 반환된다
}

ListNode* add(ListNode *list, element item) {
	int size = get_length(list);
	ListNode *temp = list; //임시 노드 선언
	//인자로 받은 리스트에서 길이를 받아온다. 값을 늘려줄거기 때문에 1을 늘려준다
	int *arr = (int *)malloc(sizeof(int)*size + 1); //arr 배열을 만들고 동적할당을 진행한다.
	for (int i = 0; i < size; i++) { //연결리스트가 가진 길이만큼 반복
		arr[i] = temp->val; //arr 배열에 temp 가 가진 값 할당
		temp = temp->next; //temp 는 옆자리로 옮긴다
	}
	arr[size] = item; //arr 의 마지막 인덱스에 인자로 받은 item 할당

	quick_sort(0, size, arr); //퀵정렬을 사용하여 arr 배열 정렬
	list = clear(list);//리스트 초기화
	for (int i = 0; i <= size; i++) {
		list = insert_last(list, arr[i]); //arr 배열이 정렬된 상태이므로 list 의 마지막에 arr[i] 추가
	}
	return list; //바뀐 list 포인터 반환

}
