/*
Google Interview Qs

Longest Univalue Path
  Go to Discuss
Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2
Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/*以下方法是别人的...
*/
class Solution {
public:
	int mmax;
	int height(TreeNode* root) {
		if (root == NULL) return 0;
		int leftHeight = height(root->left);
		int rightHeight = height(root->right);

		int left = 0;
		if (root->left != NULL && root->left->val == root->val) {
			left = leftHeight + 1;
		}
		int right = 0;
		if (root->right != NULL && root->right->val == root->val) {
			right = rightHeight + 1;
		}
		mmax = max(mmax, left + right);
		return max(left, right);

	}
	int longestUnivaluePath(TreeNode* root) {
		mmax = 0;
		height(root);
		return mmax;
	}
};

int main() {
	Solution s;
	vector<int> nums = { 1,3,1 };

	system("pause");
	return 0;

}
