/*
Write a function to connect all the adjacent nodes at the same level in a binary tree. Structure of the given Binary Tree node is like following.

struct node{
  int data;
  struct node* left;
  struct node* right;
  struct node* nextRight;  
}
Initially, all the nextRight pointers point to garbage values. Your function should set these pointers to point next right for each node.

Example

Input Tree
       A
      / \
     B   C
    / \   \
   D   E   F


Output Tree
       A--->NULL
      / \
     B-->C-->NULL
    / \   \
   D-->E-->F-->NULL
*/

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <stack>
using namespace std;

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
	struct TreeNode* nextRight;
	// constructor
	TreeNode(int x) : val(x), left(NULL), right(NULL), nextRight(NULL) {}
};

class ConnectedTree {

public:
	/*
	Method 1:
	第一步，先用findHeight func找到当前Tree的高度
	第二步，用queue_specificLevel func遍历每一层的node，放入queue中
	第三步，遍历queue，一次连接queue中元素
	*/
	void connectTree(TreeNode* root) {
		int height = findHeight(root);
		queue<TreeNode*> q;


		for (int i = 0; i <= height; i++) {
			queue_specificLevel(root, i, q);
			// former line pushed all nodes in a specific level into a queue, 
			//	start pop and connect now
			if (!q.empty()) {
				TreeNode* curNode = q.front();
				q.pop();
				while (!q.empty()) {
					curNode->nextRight = q.front();		// connect former node with queue front
					curNode = q.front();				// 
					q.pop();
				}
			}
		}
	}
	/* go to specific level, put all node into a queue (from left to right) */
	void queue_specificLevel(TreeNode* root, int whichLevel, queue<TreeNode*>& q) {
		if (root == NULL)
			return;

		// whichLevel initially = height, scan all levels
		if (whichLevel == 1) {
			q.push(root);
		}
			
		else if (whichLevel > 1) {
			// print left child first
			queue_specificLevel(root->left, whichLevel - 1, q);
			// then print right child
			queue_specificLevel(root->right, whichLevel - 1, q);
		}
	}
	/* recursively find the height of a tree
	height is the longest path from root to a leaf
	*/
	int findHeight(const TreeNode* root) {
		if (root == NULL)
			return 0;
		else {
			int leftHeight = findHeight(root->left);
			int rightHeight = findHeight(root->right);

			if (leftHeight > rightHeight)
				return (leftHeight + 1);
			else
				return (rightHeight + 1);
		}

	}



};


int main() {
/* Constructed binary tree is
            10
          /   \
        8      2
      /			\ 
    3			6
				/\
			  11	12
  */
	struct TreeNode *root = new TreeNode(10);
	root->left        = new TreeNode(8);
	root->right       = new TreeNode(2);
	root->right->right = new TreeNode(6);
	root->right->right->left = new TreeNode(11);
	root->right->right->right = new TreeNode(12);

	root->left->left  = new TreeNode(3);
 
	// Populates nextRight pointer in all nodes
	ConnectedTree ct;
	ct.connectTree(root);


	// Let us check the values of nextRight pointers
	printf("Following are populated nextRight pointers in the tree "
	"(-1 is printed if there is no nextRight) \n");
	printf("nextRight of %d is %d \n", root->val,
	root->nextRight? root->nextRight->val : -1);
	printf("nextRight of %d is %d \n", root->left->val,
	root->left->nextRight? root->left->nextRight->val : -1);
	printf("nextRight of %d is %d \n", root->right->val,
	root->right->nextRight? root->right->nextRight->val : -1);
	printf("nextRight of %d is %d \n", root->left->left->val,
	root->left->left->nextRight? root->left->left->nextRight->val : -1);

    system("pause");
    return 0;
}

