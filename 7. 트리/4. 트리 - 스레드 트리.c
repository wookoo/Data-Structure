#include <stdio.h>
#include <stdlib.h>
typedef union
{
	int number;
	char sign;

}element;

struct tree {
	element element;

	struct tree *left;
	struct tree *right;
	int is_thread;
};

typedef struct tree TreeNode;

void inorder(element* arr, int index) {
	if (arr[index].number != 0) {
		inorder(arr, 2 * index);
		if (is_leaf(arr, index)) {
			printf("[%d]", arr[index].number);
		}
		else {
			printf("[%c]", arr[index].sign);
		}
		inorder(arr, 2 * index + 1);
	}
}
int is_leaf(TreeNode *t) {
	return (t->left == NULL || t->right == NULL);
}


TreeNode *create(int data, TreeNode *left, TreeNode *right, int is_thread) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->element.number = data;
	temp->left = left;
	temp->right = right;
	temp->is_thread = is_thread;
	return temp;
}
TreeNode* find(TreeNode *p) {
	TreeNode *q = p->right;
	if (q == NULL || p->is_thread == 1) {
		return q;
	}
	while (q->left != NULL) q = q->left;
	return q;
}
void thread_in(TreeNode *t) {
	TreeNode *q;
	q = t;
	while (q->left) q = q->left;
	do {
		if (is_leaf(q)) {
			printf("[%d]", q->element.number);
		}
		else {
			printf("[%c]", q->element.number);
		}

		q = find(q);
	} while (q);
}


int main() {
	TreeNode *n4 = create(3, NULL, NULL, 1);
	TreeNode *n5 = create(2, NULL, NULL, 1);
	TreeNode *n6 = create(5, NULL, NULL, 1);
	TreeNode *n7 = create(6, NULL, NULL, 0);
	TreeNode *n2 = create('*', n4, n5, 0);
	TreeNode *n3 = create('/', n6, n7, 0);
	TreeNode *root = create('+', n2, n3, 0);
	n4->right = n2;
	n5->right = root;
	n6->right = n3;
	thread_in(root);

}
