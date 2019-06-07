#include <stdio.h>
#define MAXSIZE 100
#include <string.h> //strtok 를 사용하기 위한 string 헤더 포함
typedef int element; //char , int 형, 포인터를 저장할 변수, int 형이 포인터값 (2byte), char 값(2byte) 보다 크므로 저장 가능
typedef struct {
	element data[MAXSIZE]; //스택 구조체 정의
	int top; 
}Stack; //스택으로 데이터 타입 선언

typedef struct tree { //이진트리 구조체 생성
	element data; //이진트리는 데이터
	struct tree *left; //왼쪽 자식트리
	struct tree *right; //오른쪽 자식트리를 갖는다.
}TreeNode;

typedef Stack* Stack_Ptr; //스택 포인터 정의
//함수 원형 정의부 시작
void initStack(Stack_Ptr StackPointer);
int is_empty(Stack stack);
element pop(Stack_Ptr StackPointer);
void push(Stack_Ptr StackPointer, element data);
int is_full(Stack stack);
element peek(Stack stack);
char get_symbol(char *s);
int pis(char sym);
int pie(char sym);
char* postfix(char *String);
int is_sign(char *sign);
TreeNode *create(int data, TreeNode *left, TreeNode *right);
TreeNode* MakeRoot();
void inorder(TreeNode *root);
int is_leaf(TreeNode *root);
int eval(TreeNode *root);

//함수 원형 정의부 끝

int main() {
	/*
		알고리즘은 다음과 같다.
		1.문자열을 받아온다
		2.문자열에서 숫자, 부호를 판별한다
		3.판별된 문자를 공백을 기준으로 분리한다 
			3 - 1. 예를들여 34 + 4 면 344+ 가 되므로, 34 4 + 로 구분하기 위함
		4. 공백을 기준으로 strtok 함수를 사용하여 문자를 분리한후, 부호인지 확인한다
		5. 부호가 아니면, atoi 함수를 사용하여, 숫자로 만들고 스택에 넣는다
		6. 부호면, 스택에서 pop 을 두번 수행 한후, 트리로 만들고 스택에 넣는다.
		7. 이 작업을 반복하고 root 노드를 반환하면 된다.
	*/
	char String[] = "5+4*(75+4)-5";
	char *temp = postfix(String);
	//printf("%s\n", temp);
	/*char *ptr = strtok(temp, " ");
	while (ptr != NULL) {

		if (is_sign(ptr)) {
			printf("%c\n", ptr[0]);
		}

		ptr = strtok(NULL, " ");
	}*/
	//5 4 75 4 + * + 5 -
	free(temp);
	TreeNode *root = MakeRoot(); //기술한 알고리즘 토대로 root 를 만든 후 반환한다.
	printf("%d", eval(root)); //계산 결과 출력
	return 0;

}



void initStack(Stack_Ptr StackPointer) { //스택 초기화, 원본 데이터 수정해야 하므로 StackPtr 을 받아옴
	StackPointer->top = -1; //스택의 top 을 -1 로 초기화 해준다
}


int is_empty(Stack stack) { //스택이비었나 확인, 원본데이터 수정하면 안되므로 Stack 을 받아옴
	return (stack.top == -1); //top 이 -1 이면 1, -1이 아니면 0 반환
}

element pop(Stack_Ptr StackPointer) { //스택 pop 연산, 원본 데이터 수정해야하므로 stackPtr 을 받아옴
	if (is_empty(*StackPointer)) { //스택이 비었으면 pop 이 수행이 불가하다
		printf("더이상 pop 을 수행할수 없습니다."); //그러므로 오류메세지 출력후
		exit(1); //프로그램 종료
	}
	//스택이 안비었으면 정상적으로 pop 이 수행된다
	element temp = StackPointer->data[StackPointer->top]; 	//반환할 값을 할당
	StackPointer->top -= 1; //top 을 -1 을 해준다 > 값이 삭제되는것 처럼 보임
	return temp; //값 반환
}

void push(Stack_Ptr StackPointer, element data) { //push 연산, 원본 데이터 수정해야 하므로 stackptr 을 받아옴
	if (is_full(*StackPointer)) { //스택이 꽉찼으면 push 수행불가
		printf("더이상 push 를 수행 할 수 없습니다.");
		exit(1);//프로그램 종료
	}
	StackPointer->top += 1; //스택이 안꽉찼으면 top 을 1 증가시키고
	StackPointer->data[StackPointer->top] = data; //증가시킨 인덱스에 data 를 삽입
}

int is_full(Stack stack) { //스택이 꽉찼나 확인하는 함수
	return(stack.top == MAXSIZE-1); //배열의 최대 사이즈와 top 이 같으면 1, 아니면  0 반환
	// > 스택은 top 을 기준으로 데이터 삽입을 판단하기 때문
}

element peek(Stack stack) { //peek 함수, 스택의 상단 값 확인, 원본 수정되면 안되므로 stack 을 받아옴 
	if (is_empty(stack)) { //스택이 비어있으면 peek 이 불가하다
		printf("peek 수행 불가!");
		exit();
	}
	return (stack.data[stack.top]); //그게 아니면 최상단 값을 반환한다.
}

char get_symbol(char *s) {
	static int index = 0;
	if (s[index] != NULL) {
		return s[index++];
	}
	return NULL;
}
int pis(char sym) {
	switch (sym) {
	case '(': return 0;
	case ')': return 3;
	case '+':case'-': return 1;
	case '*':case'%':case'/': return 2;
	}
	return -1;
}
int pie(char sym) { //잘 보면 59 번 60번 라인과 68번 69번 라인의 리턴값이 바뀐것을 볼 수 있다.
	switch (sym) {
	case '(': return 3;
	case ')': return 0;
	case '+':case'-': return 1;
	case '*':case'%':case'/': return 2;
	}
	return -1;
}
char* postfix(char *String) {
	Stack stack;
	initStack(&stack);

	char *temp = (char *)malloc(sizeof(char) * 100);
	int index = 0;
	char sym;
	while ((sym = get_symbol(String)) != NULL) {
		int token = pie(sym);
		if (sym == ')') {
			char left;
			while ((left = pop(&stack)) != '(') {
				temp[index] = ' ';
				temp[++index] = left;
				temp[++index] = NULL;
			}
		}
		else if (pie(sym) == -1) {
			temp[index] = sym;
			temp[++index] = NULL;
		}
		else {
			if (sym != '(' && sym != ')') {
				temp[index] = ' ';
				temp[++index] = NULL;
			}
			while ((is_empty(stack) != 1) && (pis(peek(stack)) >= pie(sym))) {
				temp[index] = pop(&stack);
				temp[++index] = ' ';
				temp[++index] = NULL;
			}
			push(&stack, sym);
		}

	}
	while (is_empty(stack) != 1) {
		temp[index] = ' ';
		temp[++index] = pop(&stack);
		temp[++index] = NULL;

	}

	return temp;
}
int is_sign(char *sign) {
	return !(strcmp(sign, "+") != 0 && strcmp(sign, "-") != 0 && strcmp(sign, "/") != 0 && strcmp(sign, "*") != 0 && strcmp(sign, "^"));
}

TreeNode *create(int data, TreeNode *left, TreeNode *right) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->data = data;
	temp->left = left;
	temp->right = right;
	return temp;
}

TreeNode* MakeRoot() {
	char String[] = "5 4 75 4 + * + 5 -";
	//1. 스택에 때려박고
	// 연산자가 나오면 두가지를 pop 수행
	Stack stack;
	initStack(&stack);
	TreeNode *node;

	char *split = strtok(String, " ");
	while (split != NULL) {
		node = create(0, NULL, NULL);
		if (!is_sign(split)) {
			int data = atoi(split);
			node->data = data;
		}
		else {
			node->right = (TreeNode *)pop(&stack);
			node->left = (TreeNode *)pop(&stack);
			node->data = split[0];
		}
		push(&stack, (int)node);
		split = strtok(NULL, " ");
	}
	return (TreeNode *)pop(&stack);

}
void inorder(TreeNode *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%d]", root->data);
		inorder(root->right);
	}
}
int is_leaf(TreeNode *root) {

	return  (root->left == NULL && root->right == NULL);
}
int eval(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}
	if (is_leaf(root)) {
		return root->data;
	}
	int op1 = eval(root->left);
	int op2 = eval(root->right);
	printf("%d %c %d 를 계산합니다\n", op1, root->data, op2);
	switch (root->data)
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}
	return 0;
}

