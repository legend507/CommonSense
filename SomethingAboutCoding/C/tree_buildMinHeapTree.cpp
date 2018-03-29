/*
(Attention, NOT BinarySearchTree)
一下class将一个 unordered Binary Tree转化为 balanced binary tree
并且每个root节点都要比其child小
这种tree叫min heap tree
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
	// constructor
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}

	/*
	按以下func比较并排序，结果是ascending*/
	static bool compare(TreeNode* obj1, TreeNode* obj2) {
		/*注意：
		更改下面 <为>，就可以建立maxHeapTree*/
		return (obj1->val < obj2->val);
	}

};

class TreeOrder {
public:
	/*
	有参考价值
	以下func返回树的节点数，
	同时将每个节点的address放到arr中*/
	int vectorizeTreeRecurse(TreeNode* root, int count, vector<TreeNode*>& arr) {
		// base case
		// return is # of node in tree
		if (root == NULL) return count;

		// 先放root，再放left child，是按DFS顺序放入arr
		arr.push_back(root);
		count++;
		count = vectorizeTreeRecurse(root->left, count, arr);
		count = vectorizeTreeRecurse(root->right, count, arr);

		return count;
	}

	/*
	pass a pointer by reference
	下面func先将树中的节点按大小排序，然后从新建立树
	新树的父节点都比子节点小*/
	void heapifyBinaryTree(TreeNode* &root) {
		vector<TreeNode*> arr;
		int size = vectorizeTreeRecurse(root, 0, arr);

		// 排序，按升序排列
		sort(arr.begin(), arr.end(), TreeNode::compare);

		for (int i = 0; i < size; i++) {
			//为什么这样，参考heap sort
			// 这样建立的树，每个父节点都比子节点小
			int leftIdx = 2 * i + 1;
			int rightIdx = 2 * i + 2;
			if (leftIdx < size)		arr[i]->left = arr[leftIdx];
			if (rightIdx < size)	arr[i]->right = arr[rightIdx];
		}

		root = arr[0];

	}

};


int main() {

	/* Create following tree as first balanced BST
	900
	/  \
	12    13
	/ \
	100  200
	*/
	TreeNode *root1 = new TreeNode(900);
	root1->left = new TreeNode(12);
	root1->right = new TreeNode(13);
	root1->left->left = new TreeNode(100);
	root1->left->right = new TreeNode(200);

	TreeOrder to;

	/*下面方法之后，tree变成
	12
	/		\
	13		100
	/		\
	200		900
	*/
	to.heapifyBinaryTree(root1);

	system("pause");
	return 0;
}

