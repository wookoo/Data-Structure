/*
	* ���� 
	*	��ȣ������ �� ���ڿ��� �޾Ƽ� �� ���ڿ��� �ùٸ� ��ȣ������ Ȯ���Ѵ�.
	
	* ���
	*	�ùٸ� ��ȣ ���̸� parentheses are balanced �� ����Ѵ�.
	*	�ùٸ��� ���� ��ȣ ���̸� parentheses are NOT balanced �� ����Ѵ�.
	
	*�˰���
	*	������ ����Ͽ� ������ �Ѵ�. 
	*	������ ����ִ� ���¿��� ) �� ������ �� �迭�� NOT balanced ��.
	*	������ ������� �ʴ� ���¿��� ) �� ������, ) �� �������� �ʰ�, �������� ������ ( �� �����Ѵ�.
	*	���ڿ��� NULL �� �ƴҶ� ���� �ݺ��� �Ѵ�.
	
	*�Լ�
	*	void init(stack_type_ptr inputStack) : stack �� �ʱ�ȭ�Ѵ�.
	*	void push(stack_type_ptr inputStack, element data) : stack�� �޾ƿ� data �� �ִ´�.
	*	int is_empty(stack_type inputStack) : stack�� ������� Ȯ���Ѵ�.
	*	int is_full(stack_type inputStack) : ������ ��á���� Ȯ���Ѵ�.
	*	element pop(stack_type_ptr inputStack) : ������ ������ �־��� ���� ����� ��ȯ�Ѵ�.
	*	char get_symbol(char s[]) : ȣ���Ҷ� ���� ���ڿ� �迭 s �� 0��°...1��°... n ��° �ε��� ���� ��ȯ�Ѵ�.
	*	int paren_test(char s[]) : balanced ���� Not balanced ���� Ȯ���Ѵ�.
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
int paren_test(char s[]);//balanced ���� Not balanced ���� Ȯ���Ѵ�.


int main() {


	char string[] = "()()(((()())))";
	int check = paren_test(string); //paren_test �� "())()(((()())))" ���� ������� check �� �Ҵ��Ѵ�.
	if (check) //1�� ��ȯ�Ǹ� balanced �ϴ�
	{
		printf("parentheses are balanced\n");
	}
	else { // 0�� ��ȯ�Ǿ����� Not balanced �ϴ�
		printf("parentheses are NOT balanced");
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

int paren_test(char s[]) {// balanced ���� Not balanced ���� Ȯ���ϴ� �Լ���.
	stack_type stack; //Ȯ���� ���ؼ� ������ �ʿ��ϱ� ������ ������ �����Ѵ�.
	init(&stack); //������ ������ �ʱ�ȭ�Ѵ�.
	char temp; //�ӽ÷� ����� char ����, while �� ��Ʈ�� �� if ���� ���ȴ�.
	int IsTrue = 1; //�� ������ �Ǻ��ϴ� ������. �ʱⰪ�� 1 (��)���� �Ѵ�.
	while ((temp = get_symbol(s)) != NULL) { //temp �� get_sybol �� ��ȯ���ε�, �װ��� NULL �� �ƴҶ� ���� �ݺ�
		if (is_empty(stack) == 1 && temp == ')') { //������ �� ��Ȳ�ε� ) �� ���� ������ ) ���� �ȴ�.
			IsTrue = 0;	//�̴� �� ���� ���� ��ȣ���� �ǹ��ϱ⿡ false �� �����.
			break; //���̻� �� ��ġ�� �����Ƿ� ������ �����Ѵ�.
		}
		if (temp == ')') { //���� if ���� ������ �ȵǹǷ� �ش� ������ �����̵ȴ�.
			//���� ���� ) ���
			pop(&stack); //���ÿ� (....(( �÷� ����Ǿ��ֱ⿡ ������ ( �� ����� 
			//(....( �̷������� ���̴�.
		}
		else {
			push(&stack, temp); //�ƴ� ��� ���� ( �� ������ ���⿡ ���ÿ� �����Ѵ�.
		}



	}
	return IsTrue; //�� ������ ��ȯ�� ���ش�.
}

