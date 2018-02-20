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

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {

	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {

	}

	/* ---------------------------BFS ------------------------------------------------------
	从最上层开始逐层扫描，先打印 左孩子，再打印 右孩子
	*/
	void print_BFS(TreeNode* root) {
		// calc height of the input tree
		int height = findHeight(root);
		for (int i = 1; i <= height; i++)
			print_specificLevel(root, i);

		cout << "	End Of BFS" << endl;
	}

	/* ------------------------DFS---------------------------------------------------------
	以下Code是先从root开始，先看左孩子，最后看右孩子的顺序（aka. Preorder）
	通过改变 print行和 看左孩子，右孩子的行的顺序可以实现 Inorder/Postorder 遍历
	*/
	void print_DFS_preorder(TreeNode* root) {

		// 应为想在最后输出End，所以多写了一个子函数
		print_oneNode(root);

		cout << "	End Of DFS" << endl;
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
			int leftHeight	= findHeight(root->left);
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

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
int main() {
	Codec codec;

	TreeNode root(1);	

	root.left = new TreeNode(2);
	root.left->right = new TreeNode(100);

	root.right = new TreeNode(3);
	root.right->left = new TreeNode(4);
	root.right->right = new TreeNode(5);

	codec.print_DFS_preorder(&root);

	system("pause");
	return 0;

}
