/*
Invert a binary tree.

Example:

Input:

     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1
Trivia:
This problem was inspired by this original tweet by Max Howell:

Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so f*** off.
问题挺简单，以下是我自己写的solution，但问题背后的故事挺有意思*/
#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	TreeNode * invertTree(TreeNode* root) {
		doRecurse(root);
		return root;
	}

	void doRecurse(TreeNode* root) {
		// base case
		if (root == NULL)	return;

		// recurse case
		TreeNode* curLeft = root->left;
		TreeNode* curRight = root->right;
		doRecurse(root->left);
		doRecurse(root->right);

		root->left = curRight;
		root->right = curLeft;
	}

};

int main() {

	system("pause");
	return 0;

}
