/*
一下Class实装 Binary Search Tree
- insert 
- deleteNode

Insertion/removal/lookup: O(logn)

*/

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <stack>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	// Constructor
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class MyBST {
	TreeNode* root;

	/*find the min element from curRoot*/
	TreeNode* returnMinNode(TreeNode* curRoot) {
		while (curRoot->left != NULL)	curRoot = curRoot->left;

		return curRoot;
	}

	/*
	Logic是，先recursive找到这个element所在的node(curRoot)
	然后分 curRoot 有一个孩子(include没孩子的情况)，和有两个孩子的请款
	- 如果有一个孩子，就用那个孩子代替curRoot
	- 如果有两个孩子，则在curRoot->right中找到minNode，用minNode代替curRoot，然后把minNode原来的位置删除
	*/
	TreeNode* deleteRecurse(TreeNode* curRoot, int element) {
		// base case
		if (curRoot == NULL)	return curRoot;

		// element too small, go left
		if (element < curRoot->val) curRoot->left = deleteRecurse(curRoot->left, element);
		// element too big, go right
		else if (element > curRoot->val)	curRoot->right = deleteRecurse(curRoot->right, element);
		//found, curRoot is the one
		else {
			// check the child numer of root 
			/// if only have one child, or no child
			if (curRoot->left == NULL) {
				// delete curRoot, and put its right child to curRoot's position
				TreeNode* temp = curRoot->right;
				delete curRoot;
				return temp;
			}
			else if (curRoot->right == NULL) {
				// delete curRoot, and put its left child to curRoot's position
				TreeNode* temp = curRoot->left;
				delete curRoot;
				return temp;
			}

			// if curRoot has both right and left child
			/*by inputing curRoot->right, the following func returns
			比curRoot的val大的最小val (注意这里！！)*/
			TreeNode* temp = returnMinNode(curRoot->right);	// temp is the node that has min val on curRoot->right branch
			curRoot->val = temp->val;		// <- This line deletes element
			curRoot->right = deleteRecurse(curRoot->right, temp->val); // 因为已经把temp的val放到curRoot中了，所以删除temp
		}
		return curRoot;
	}

public:
	MyBST() : root(NULL) {}

	/*
	插入新element*/
	int insert(int element) {
		// 插第一个node
		if (root == NULL) {
			root = new TreeNode(element);
			return 0x00;
		}

		TreeNode* curRoot = root;
		TreeNode* nextNode = curRoot;

		/*
		一下while找到一个既存node，
		通过比较val和element的大小决定插坐还是插右*/
		while (nextNode != NULL) {
			curRoot = nextNode;
			// element too small, go left
			if (curRoot->val >= element) {
				nextNode = curRoot->left;
			}
			// element big, go right
			else {
				nextNode = curRoot->right;
			}
		}

		(curRoot->val >= element) ? curRoot->left = new TreeNode(element) : curRoot->right = new TreeNode(element);

		return 0x00;
	}


	int deleteNode(int element) {
		root = deleteRecurse(root, element);
		return 0x00;
	}

};


int main() {
	MyBST myBST;

	 /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 
					/
					71
	   */

	myBST.insert(50);
	myBST.insert(30);
	myBST.insert(20);
	myBST.insert(40);
	myBST.insert(70);
	myBST.insert(60);
	myBST.insert(80);
	myBST.insert(71);

	myBST.deleteNode(80);

	myBST.deleteNode(50);

	system("pause");
	return 0;
}

