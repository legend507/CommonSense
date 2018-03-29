/*
一下是Tree Rotate的实装，
ToDo：本想实装MyAVL的，但是有些复杂，先放着
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

// a structure of TreeNode
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	int height;
	// constructor, height = 1 because every inserted node stated as a leaf
	TreeNode(int x) : val(x), left(NULL), right(NULL), height(1) {}

};

class MyAVL {
	TreeNode * root;

public:
	MyAVL() :root(NULL) {}


	/*
		oR					nR
		/\			=>		/\
	 nR		...			  ... oR
	 / \					  /\
	... nRR					nRR ...
	解释一下就是，把原root的left child当成新root，原root放到新root的right child
	新root的以前的right child放到原root的left child上
	*/
	int rightRotate() {
		TreeNode* oldRoot = root;						// old root
		TreeNode* newRoot = root->left;					// new root (old root's left child)
		TreeNode* newRootRight = root->left->right;		// new root's original right child

		// rotate
		newRoot->right = oldRoot;			// set old root as left child of new root
		oldRoot->left = newRootRight;		// move new root's original right child to old root's left

		// update height
//		newRoot->height = max(newRoot->left->height, newRoot->right->height) + 1;
//		oldRoot->height = max(oldRoot->left->height, oldRoot->right->height) + 1;

		root = newRoot;
		return 0x00;
	}
	int leftRotate() {
		TreeNode* oldRoot = root;
		TreeNode* newRoot = root->right;
		TreeNode* newRootLeft = root->right->left;

		// rotate
		newRoot->left = oldRoot;
		oldRoot->right = newRootLeft;

		// update height
//		oldRoot->height = max(oldRoot->left->height, oldRoot->right->height) + 1;
//		newRoot->height = max(newRoot->left->height, newRoot->right->height) + 1;

		root = newRoot;
		return 0x00;
	}

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


};


int main() {
	MyAVL ma;
	
	ma.insert(0);
	ma.insert(1);
	ma.insert(2);
	ma.insert(3);
	ma.insert(4);
	ma.insert(5);


	ma.leftRotate();


	system("pause");
	return 0;
}

