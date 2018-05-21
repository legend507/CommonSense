﻿/*
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
	/*Not Efficient*/
	bool isBST(TreeNode* root) {
		// base case
		if (root == NULL)	return true;

		// recurse case
		//	false if the max of the left is > than root->val
		if (root->left != NULL && findMaxValue(root->left) > root->val)		return false;

		//	false if the min of the right is < than root->val
		if (root->right != NULL && findMinValue(root->right) < root->val)	return false;

		//	false if left or right is not a BST
		if (!isBST(root->left) || !isBST(root->right))	return false;

		return true;

	}

	int findMaxValue(TreeNode* root) {
		// base case
		if (root == NULL)	return INT_MIN;

		// recurse case
		return max(root->val, findMaxValue(root->left), findMaxValue(root->right));
	}
	int findMinValue(TreeNode* root) {
		// base case
		if (root == NULL)	return INT_MAX;

		// recurse case
		return min(root->val, findMaxValue(root->left), findMaxValue(root->right));
	}
};

int main()
{
	Solution s;

	system("pause");
	return 0;
}

