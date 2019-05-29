#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode{
	struct TreeNode *left;
	int data;
	struct TreeNode *right;
}TreeNode;

void preorder(TreeNode *root) {
	if (root != NULL) {
		printf("[%d]", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(TreeNode *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%d]",root->data);
		inorder(root->right);
	}
}

void postorder(TreeNode *root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d]", root->data);
	}
}

TreeNode* gen_tree(int data) {
	TreeNode *result = (TreeNode *)(malloc(sizeof(TreeNode)));
	result->data = data;
	result->right = NULL;
	result->left = NULL;
	return result;
}
void MakeLeftSubTree(TreeNode *main,TreeNode *sub) {
	main->left = sub;
}
void MakeRightSubTree(TreeNode *main, TreeNode *sub) {
	main->right = sub;
}


int main() {
	TreeNode *root = gen_tree(5);
	TreeNode *n1 = gen_tree(4);
	TreeNode *n2 = gen_tree(7);
	TreeNode *n3 = gen_tree(9);
	TreeNode *n4 = gen_tree(6);
	TreeNode *n5 = gen_tree(3);
	TreeNode *n6 = gen_tree(2);
	TreeNode *n7 = gen_tree(1);
	MakeLeftSubTree(root, n1);
	MakeRightSubTree(root, n2);
	MakeLeftSubTree(n1, n3);
	MakeRightSubTree(n1, n4);
	MakeRightSubTree(n3, n6);
	MakeRightSubTree(n2, n5);
	MakeLeftSubTree(n5, n7);
	printf("전위 순서");
	preorder(root);
	printf("\n");
	printf("중위 순서");
	inorder(root);
	printf("\n");
	printf("후위 순서");
	postorder(root);
	printf("\n");
}
