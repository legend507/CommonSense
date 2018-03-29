#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
using namespace std;


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	// Constructor
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

	/*下面的func检查当前树是否是balanced tree*/
	bool isBalanced(TreeNode* root) {
		int leftHeight = 0;
		int rightHeight = 0;

		// if a tree is empty, then it is balanced
		if (root == NULL)
			return true;

		//
		leftHeight = findHeight(root->left);
		rightHeight = findHeight(root->right);

		if (abs(leftHeight - rightHeight) <= 1 &&	/*for current root, left and right height diff <= 1*/
			isBalanced(root->left) &&				/*check left subtree is balanced*/
			isBalanced(root->right))				/*check right subtree is balanced*/
			return true;

		return false;

	}

	/* ---------------------------BFS ------------------------------------------------------
	从最上层开始逐层扫描，先打印 左孩子，再打印 右孩子
	*/
	// recursive version
	void print_BFS(TreeNode* root) {
		// calc height of the input tree
		int height = findHeight(root);
		for (int i = 1; i <= height; i++)
			print_specificLevel(root, i);

		cout << "	End Of BFS" << endl;
	}

	// no recursive version
	void print_BFS_noRecursive(TreeNode* root) {
		queue<TreeNode>	bfsQueue;
		bfsQueue.push(*root);

		while (!bfsQueue.empty()) {
			TreeNode oneNode = bfsQueue.front();
			bfsQueue.pop();

			cout << oneNode.val << " ";			// <------------ This line prints val

			if (oneNode.left != NULL) {
				bfsQueue.push(*(oneNode.left));
			}
			if (oneNode.right != NULL) {
				bfsQueue.push(*(oneNode.right));
			}
		}
		cout << "	End Of BFS (no recursion)" << endl;
	}

	/* ------------------------DFS---------------------------------------------------------
	以下Code是先从root开始，先看左孩子，最后看右孩子的顺序（aka. Preorder）
	通过改变 print行和 看左孩子，右孩子的行的顺序可以实现 Inorder/Postorder 遍历
	*/
	// recursive version
	void print_DFS_preorder(TreeNode* root) {

		// 应为想在最后输出End，所以多写了一个子函数
		print_oneNode(root);

		cout << "	End Of DFS" << endl;
	}
	// no recursive version
	void print_DFS_preorder_noRecursive(TreeNode* root) {
		stack<TreeNode> dfsStack;
		dfsStack.push(*root);

		while (!dfsStack.empty()) {
			TreeNode oneNode = dfsStack.top();
			dfsStack.pop();

			cout << oneNode.val << " ";			// <------------ This line prints val

			if (oneNode.right != NULL)
				dfsStack.push(*oneNode.right);

			if (oneNode.left != NULL)
				dfsStack.push(*oneNode.left);


		}
		cout << "	End Of DFS (no recursion)" << endl;
	}

private:
	/*------------------------------BFS中要用的subfunc--------------------------------------------*/
	/*
	Called by print_BFS, to print all children in a specific level
	*/
	void print_specificLevel(TreeNode* root, int whichLevel) {
		if (root == NULL)
			return;

		// whichLevel initially = height, scan all levels
		if (whichLevel == 1)
			cout << root->val << " ";		// <--------- This line do the print work

		else if (whichLevel > 1) {
			// print left child first
			print_specificLevel(root->left, whichLevel - 1);
			// then print right child
			print_specificLevel(root->right, whichLevel - 1);
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

	/*------------------------------DFS中要用的subfunc--------------------------------------------*/
	void print_oneNode(TreeNode* root) {
		if (root == NULL)
			return;

		// print val
		cout << root->val << " ";

		// Traverse Left branch
		print_oneNode(root->left);
		// Traverse Right branch
		print_oneNode(root->right);
	}

};

int main() {
	Codec codec;

	/*
				1
			/		\
			2		3
			\		/\
			 100	4 5
			 \
			 200

	*/

	TreeNode root(1);

	root.left = new TreeNode(2);
	root.left->right = new TreeNode(100);
	root.left->right->right = new TreeNode(200);

	root.right = new TreeNode(3);
	root.right->left = new TreeNode(4);
	root.right->right = new TreeNode(5);

	codec.print_DFS_preorder(&root);
	codec.print_DFS_preorder_noRecursive(&root);

	codec.isBalanced(&root) ? cout << "yes" : cout << "no";

	system("pause");
	return 0;

}
