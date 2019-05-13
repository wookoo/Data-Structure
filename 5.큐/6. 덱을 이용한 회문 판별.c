#include <stdio.h>
#include <stdlib.h>
#define MAX_QUE_SIZE 10
typedef int element;
typedef struct { //���� ť�� ������ front rear �ʵ�
	int front;
	int rear;
	element data[MAX_QUE_SIZE]; //�����͸� �����ϴ� �迭
} Deque;

typedef  Deque* Deque_ptr;

//�Լ� ���� ���� �� ����
void error(char *String);
void init(Deque_ptr dq);
int is_empty(Deque_ptr dq);
int is_full(Deque_ptr dq);
element delete_front(Deque_ptr dq);
void add_rear(Deque_ptr dq, element data);
void add_front(Deque_ptr dq, element data);
element delete_rear(Deque_ptr dq);
char get_symbol(char *String);

//�Լ� ���� ���Ǻ� ��

int main() {
	Deque a;
	Deque_ptr dq = &a;
	init(dq);
	char String[] = "abcba";
	char sym;
	int IsTrue = 1; //String �� ������ �������� Ȯ���ϱ� ���� ����
	while ((sym = get_symbol(String)) != NULL) {
		add_rear(dq, sym); //String �� ��� ��Ҹ� ���� ����
	}
	while (!is_empty(dq)) { //���� ���� ������ ���� �ݺ�
		char front;
		front = delete_front(dq); //�ϴ� ���� ������ ���� �ϹǷ� ���鿡�� ���� �����´�

		if (!is_empty(dq)) { //���ڿ��� ¦���� ���
			char rear;
			rear = delete_rear(dq); //�ĸ鿡�� ���� �����´�
			if (rear != front) { //����ο� �ĸ�� ��, ó������ ������ ���� ���� ������
				IsTrue = 0; //�װ��� ȸ���� �ƴϱ⿡ 0���� �����
				break; //while ������
			}
		}
	}

	if (IsTrue) { //ȸ���� ���� ȸ���� �ƴ� ��츦 ���
		printf("ȸ��");
	}
	else {
		printf("ȸ�� �ƴ�");
	}

	return 0; //�����Լ� ����

}


void error(char *String) { //���� ��� �Լ�
	printf("%s", String); //�Է¹��� ������ ����ϰ� ���α׷� ����
	exit(1);
}
void init(Deque_ptr dq) { //���� �ʱ�ȭ, front �� rear �� 0���� �ٲ�
	dq->front = 0;
	dq->rear = 0;
}

int is_empty(Deque_ptr dq) { //���� �� ���� front �� rear �� ���� ����
	return dq->front == dq->rear;
}
int is_full(Deque_ptr dq) { //���� ���� �� ���� rear ���� 1�� ���� ���� front �� �������
	return (dq->rear + 1) % MAX_QUE_SIZE == dq->front;


}

element delete_front(Deque_ptr dq) { //���� �տ��� ���� ����� ���
	if (is_empty(dq)) {
		error("���� ������ϴ�!");
	}
	//���� ���� ���� �ʾ�����
	dq->front = (dq->front + 1) % MAX_QUE_SIZE; //�ð�������� ���� ������
	return dq->data[dq->front]; //���� ��ȯ
}

void add_rear(Deque_ptr dq, element data) {
	if (is_full(dq)) {
		error("���� ���� á���ϴ�."); 
	}
	//���� ��������  �ʾ�����
	dq->rear = (dq->rear + 1) % MAX_QUE_SIZE; //�ð�������� ���� ������
	dq->data[dq->rear] = data; //���� ����
}

void add_front(Deque_ptr dq, element data) {
	if (is_full(dq)) { 
		error("���� ���� á���ϴ�.");
	}
	//���� ���� ���� �ʾ�����
	dq->data[dq->front] = data; //���� �����ϰ�
	dq->front = (dq->front - 1 + MAX_QUE_SIZE) % MAX_QUE_SIZE; //�ð� �ݴ�������� ���� ����
	
}

element delete_rear(Deque_ptr dq) {
	if (is_empty(dq)) { 
		error("���� ������ϴ�!");
	}
	//���� ���� �ʾ�����
	element item = dq->data[dq->rear]; //���� ��������
	dq->rear = (dq->rear - 1 + MAX_QUE_SIZE) % MAX_QUE_SIZE; //�ð� �ݴ�������� ���� ������
	return item; //���� ��ȯ
}
char get_symbol(char *String) { //for strlen(String) �� �����
	static int index = 0; //static ���� ����, �Լ� call ���� 1 �� increase
	if (String[index] != NULL) { //NULL ���� �ƴϸ�
		return String[index++]; //��ȯ�� index 1 ����
	}
	else
	{
		return NULL;
	}
}

