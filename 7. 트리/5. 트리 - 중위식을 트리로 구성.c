#include <stdio.h>
#define MAXSIZE 100
#include <string.h>
typedef int element;
typedef struct {
	element data[MAXSIZE];
	int top;
}Stack;

typedef struct tree {
	element data;
	struct tree *left;
	struct tree *right;
}TreeNode;

typedef Stack* Stack_Ptr;

void initStack(Stack_Ptr StackPointer) {
	StackPointer->top = -1;
}


int  is_empty(Stack stack) {
	return (stack.top == -1);
}

element pop(Stack_Ptr StackPointer) {
	if (is_empty(*StackPointer)) {
		printf("더이상 pop 을 수행할수 없습니다.");
		exit(1);
	}
	element temp = StackPointer->data[StackPointer->top];
	StackPointer->top -= 1;
	return temp;
}

void push(Stack_Ptr StackPointer, element data) {
	if (is_full(*StackPointer)) {
		printf("더이상 push 를 수행 할 수 없습니다.");
		exit(1);
	}
	StackPointer->top += 1;
	StackPointer->data[StackPointer->top] = data;
}

int is_full(Stack stack) {
	return(stack.top == MAXSIZE);
}

element peek(Stack stack) {
	if (is_empty(stack)) {
		return NULL;
	}
	return (stack.data[stack.top]);
}

char get_symbol(char s[100]) {
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
	return !(strcmp(sign, "+") != 0 && strcmp(sign, "-") != 0 && strcmp(sign, "/") != 0 && strcmp(sign, "*") != 0 && strcmp(sign,"^") );
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

int main() {
	char String[] = "5+4*(75+4)-5";
	char *temp = postfix(String);
	//printf("%s\n", temp);
	char *ptr = strtok(temp, " ");
	while (ptr != NULL) {

		if (is_sign(ptr)) {
			printf("%c\n", ptr[0]);
		}
		
		ptr = strtok(NULL, " ");
	}
	//5 4 75 4 + * + 5 -
	free(temp);
	TreeNode *root = MakeRoot();
	//inorder(root);
	printf("%d",eval(root));
	
	//MakeRoot
}
