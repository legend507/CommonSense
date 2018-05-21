/*
A program to check if a binary tree is BST or not
A binary search tree (BST) is a node based binary tree data structure which has the following properties.
• The left subtree of a node contains only nodes with keys less than the node’s key.
• The right subtree of a node contains only nodes with keys greater than the node’s key.
• Both the left and right subtrees must also be binary search trees.

From the above properties it naturally follows that:
• Each node (item in the tree) has a distinct key.

Refer to https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	/*1. Not Efficient, because max and min need to go through tree several times*/
	bool isBST(TreeNode* root) {
		// base case
		if (root == NULL)	return true;

		// recurse case
		//	false if the max of the left is > root->val
		if (root->left != NULL && findMaxValue(root->left) > root->val)		return false;

		//	false if the min of the right is < root->val
		if (root->right != NULL && findMinValue(root->right) < root->val)	return false;

		//	false if left or right is not a BST
		if (!isBST(root->left) || !isBST(root->right))	return false;

		return true;
	}
	/*Two utility functions, to find max and min value of current binary tree*/
	int findMaxValue(TreeNode* root) {
		// base case
		if (root == NULL)	return INT_MIN;

		// recurse case
		return max(root->val, max(findMaxValue(root->left), findMaxValue(root->right)));
	}
	int findMinValue(TreeNode* root) {
		// base case
		if (root == NULL)	return INT_MAX;

		// recurse case
		return min(root->val, min(findMinValue(root->left), findMinValue(root->right)));
	}
////////////////////////////////////////////////////////////////////////////////////////////////////

	/*2. Efficient*/
	bool isBST_efficient(TreeNode* root) {
		return isBST_efficient_recurse(root, INT_MIN, INT_MAX);
	}
	/*constrain: min <= root->val <= max*/
	bool isBST_efficient_recurse(TreeNode* root, int min, int max) {
		if (root == NULL)	return true;	// empty tree is BST

											/*false if root->val is not in range*/
		if (root->val < min || max < root->val)	return false;

		return (
			isBST_efficient_recurse(root->left, min, root->val - 1)			/*max for left subtree is set to "root->val - 1"*/
			&& isBST_efficient_recurse(root->right, root->val + 1, max)		/*min for right subtree is set to "root->val + 1"*/
			);

	}

};

int main()
{
	Solution s;

	TreeNode *root = new TreeNode(4);
	root->left = new TreeNode(2);
	root->right = new TreeNode(5);
	root->left->left = new TreeNode(1);
	root->left->right = new TreeNode(3);

	cout << s.findMaxValue(root) << endl;
	cout << s.findMinValue(root) << endl;

	if (s.isBST_efficient(root)) cout << "YES";
	else cout << "NO";

	system("pause");
	return 0;
}

