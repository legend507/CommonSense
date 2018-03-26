#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<sstream>			// istringstream and ostringstream
using namespace std;


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	// Constructor
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
	Codec class可以将TreeNode结构的树 转换成 string，并将 string 转换成为 TreeNode结构树
*/
class Codec {
public:

	// Encodes a tree to a single string.
	//	use DFS to construct the string
	string serialize(TreeNode* root) {

		stringstream ret;

		/*
		DFS遍历每个node，
		如果当前node有数值，把数值放入 stringstream，在插入空格字符
		如果当前node为NULL，把“NULL ”放入stringstream
		顺序是：root - leftChild - rightChild
		*/

		DFS(root, &ret);
		return ret.str();
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {

		// 把input string转换为stream，之后就可以用 >>　操作符了
		stringstream ret(data);

		/*
		递归，ret中第一个元素是 root，然后是左孩子，然后是左孩子的左孩子... 直到看到NULL，
		然后是最近的一个node的右孩子
		*/
		return traverseString(&ret);
	}

private:
	void DFS(TreeNode* root, stringstream* ret) {
		if (root) {
			*ret << root->val << ' ';	// 1st, put root value
			DFS(root->left, ret);		// 2nd, put left child value
			DFS(root->right, ret);		// 3rd, put right child value
		}
		else {
			*ret << "NULL ";
		}
	}


	TreeNode* traverseString(stringstream * ss) {
		string val;
		*ss >> val;

		if (val == "NULL")	return NULL;

		TreeNode* newNode = new TreeNode(stoi(val));	//必须声明pointer然后new，

		newNode->left = traverseString(ss);
		newNode->right = traverseString(ss);

		return newNode;
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
	root.right->right->right = new TreeNode(101);
	root.right->right->right->left = new TreeNode(201);

	cout << codec.serialize(&root) << endl;

	codec.deserialize(codec.serialize(&root));

	system("pause");
	return 0;

}
