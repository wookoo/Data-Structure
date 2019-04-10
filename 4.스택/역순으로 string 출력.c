/*
	* ����
	*	���ڿ��� �޾Ƽ� ������ ����Ͽ� �������� ����� �Ѵ�.

	* ���
	*	abcde �� �Է��̸� edcba �� ����Ѵ�.
	*	123456 �� �Է��̸� 654321 �� ����Ѵ�.

	*�˰���
	*	������ ����Ͽ� ������ �Ѵ�.
	*	while ���� ����Ͽ� ���ڿ��� NULL �� �ƴҶ� ���� �ݺ��Ͽ� ���ÿ� �����Ѵ�.
	*	������ ���� ������ ���� ���������� �־��� ���� ����� ����ϴ� pop �Լ��� ����Ѵ�.


	*�Լ�
	*	void init(stack_type_ptr inputStack) : stack �� �ʱ�ȭ�Ѵ�.
	*	void push(stack_type_ptr inputStack, element data) : stack�� �޾ƿ� data �� �ִ´�.
	*	int is_empty(stack_type inputStack) : stack�� ������� Ȯ���Ѵ�.
	*	int is_full(stack_type inputStack) : ������ ��á���� Ȯ���Ѵ�.
	*	element pop(stack_type_ptr inputStack) : ������ ������ �־��� ���� ����� ��ȯ�Ѵ�.
	*	char get_symbol(char s[]) : ȣ���Ҷ� ���� ���ڿ� �迭 s �� 0��°...1��°... n ��° �ε��� ���� ��ȯ�Ѵ�.

*/
#define MAX_SIZE 20
#include <stdio.h>
typedef char element; //elemnet �� char �� ����.

typedef struct {
	element statck[MAX_SIZE]; //element Ÿ������ ������ statck �迭 ����
	int top;//���° �ε��� ���� ����Ǿ��ִ��� Ȯ���Ѵ�.
} stack_type;

typedef stack_type* stack_type_ptr; //stack_type �� ���� �����͸� stack_type_ptr �� �����Ѵ�.

void init(stack_type_ptr inputStack); //���� stack �� �ٲٱ� ���� stack_type_ptr ��� (���� ȣ��)
void push(stack_type_ptr inputStack, element data); //���� stack �� �ٲٱ� ���� stack_type_ptr ��� (���� ȣ��)
int is_empty(stack_type inputStack);//���� stack �� �ٲٸ� �ȵǱ� ������ stack_type ��� (�� ȣ��)
int is_full(stack_type inputStack); //���� stack �� �ٲٸ� �ȵǱ� ������ stack_type ��� (�� ȣ��)
element pop(stack_type_ptr inputStack);//���� stack �� �ٲٱ� ���� stack_type_ptr ��� (���� ȣ��)
char get_symbol(char s[]);//ȣ���Ҷ� ���� ���ڿ� �迭 s �� 0��°...1��°... n ��° �ε��� ���� ��ȯ�Ѵ�.


int main() {
	stack_type s; //���ÿ� �־�� ������ �����Ƿ� ������ �����Ѵ�.
	init(&s);	//����� ������ �ʱ�ȭ�Ѵ�.

	char string[] = "abcdef"; //����� ����� string ����
	char temp;
	while ((temp = get_symbol(string)) != NULL) { //temp �� get_sybol �� ��ȯ���ε�, �װ��� NULL �� �ƴҶ� ���� �ݺ�
		push(&s, temp); //while ���� ���̸� ���� s �� temp �� ����ִ´�.
	}

	while (is_empty(s) != 1) {//������ ���� �ʾ��� ���, call by value �̹Ƿ� �����͸� ������� �ʴ´�.
		printf("%c", pop(&s));	//������ ������ �־��� ���� ����ϰ�, �����.
	}


}

void init(stack_type_ptr inputStack) {  //stack ����ü�� �ʱ�ȭ�Ѵ�. 
	inputStack->top = -1; //�ʱ�ȭ�� top �� - 1 �� �Ѵ�.
}

void push(stack_type_ptr inputStack, element data) { //inputStack �� data �� �ִ´�.

	if (is_full(*inputStack)) { //is_full �� call by value �̹Ƿ� inputStack �� ����Ű�� ���� �ִ´�.
		//�迭�� ��á���� �����͸� �о������ ����.
		printf("���̻� �����͸� ���� �� �����ϴ�!");
		exit(1);
	}
	else {//�迭�� ������ �ʾ����Ƿ� �����͸� �о�ִ´�.
		inputStack->top += 1;  //����� top �� 1 ������Ű��
		inputStack->statck[inputStack->top] = data; //�� top �� ����� �� index �� ����Ͽ� �� �ε����� data �� �ִ´�.
	}

}

int is_empty(stack_type inputStack) { // inputStack �� ������� Ȯ���Ѵ�.
	return ((inputStack.top == -1)); //== �����ڸ� ����ؼ� -1 �̸� ���̱⶧���� 1�� ��ȯ�ȴ�.
	//�ƴϸ� 0�� ��ȯ�ȴ�.
}

int is_full(stack_type inputStack) { //inputStack �� ��á���� Ȯ���Ѵ�.

	return  (inputStack.top == (MAX_SIZE - 1)); //== �����ڸ� ����ؼ� ���̸� 1�� ��ȯ�ȴ�.
	//�׷��⶧���� ������ 1, ������ ������ 0�� ��ȯ�ȴ�.
}


element pop(stack_type_ptr inputStack) { //������ �־��� ���� ����� ��ȯ�ϴ� �Լ���.

	if (is_empty(*inputStack)) {//is_empty �� call by value �̹Ƿ� inputStack �� ����Ű�� ���� �ִ´�.
		//is_empty �� �� ��, top �� -1 �̸� ���̻� ����� ���� ������ ����ȴ�.
		printf("���̻� ����� �����ϴ�!");
		exit(1);
	}
	else {
		element returnData = inputStack->statck[inputStack->top]; //inputStack->top �� ������ ����� �ε����� �ǹ��Ѵ�.
		//�� �ε����� ���� ���� returnData �� �Ҵ��Ѵ�.
		inputStack->top -= 1; //�����͸� ����ŹǷ�  top �� -1 �Ѵ�

		return returnData; //�� �� �Ʊ� �Ҵ��� returnData �� ��ȯ�Ѵ�.
	}

}


char get_symbol(char s[]) {
	static int index = 0; //�Լ��� ȣ��ɶ����� �����ϱ� ���� static ���� ����Ѵ�.
	if (s[index] != NULL) {//���� �Ķ���ͷ� �޾ƿ� s �迭�� index ���� NULL �� �ƴϸ�
		return s[index++]; //s�� index ���� ��ȯ�ϰ� index �� 1 �����Ѵ�.
	}
	else { //�ƴ϶��
		return NULL; //NULL �� ��ȯ�Ѵ�
	}
}


