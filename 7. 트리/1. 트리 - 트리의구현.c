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

TreeNode* gen_tree(int data,TreeNode *left, TreeNode *right) {
	TreeNode *result = (TreeNode *)(malloc(sizeof(TreeNode)));
	result->data = data;
	result->right = right;
	result->left = left;
	return result;
}

int main() {
	TreeNode *n1 = gen_tree(1, NULL, NULL);
	TreeNode *n2 = gen_tree(4, n1, NULL);
	TreeNode *n3 = gen_tree(16, NULL, NULL);
	TreeNode *n4 = gen_tree(25, NULL, NULL);
	TreeNode *n5 = gen_tree(20, , n4);
	TreeNode *n6 = gen_tree(15, n2, n5);
	postorder(n6);
}
