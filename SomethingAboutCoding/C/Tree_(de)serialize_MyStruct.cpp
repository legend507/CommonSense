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

struct ArrayNode {
	int val;
	bool isLeaf;
	ArrayNode(int v, bool b) : val(v), isLeaf(b) {};

	friend ostream& operator <<(ostream& out, const ArrayNode& obj) {
		if (obj.isLeaf)
			out << " # ";
		else
			out << " " << obj.val << " ";

		return out;
	}
};

/*
Codec class可以将TreeNode结构的树 转换成 string，并将 string 转换成为 TreeNode结构树
*/
class Codec {
public:

	// Encodes a tree to a single string.
	//	use DFS to construct the string
	vector<ArrayNode> serialize(TreeNode* root) {
		vector<ArrayNode> serial;

		DFS(root, serial);

		return serial;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(vector<ArrayNode>& serial) {
		int start = 0;			// need to keep trace of serial array, hence start var
		return constructTree(serial, start);
	}

private:
	void DFS(TreeNode* root, vector<ArrayNode>& serial) {
		if (root == NULL) {
			serial.push_back(ArrayNode(0, true));
		}
		else {
			serial.push_back(ArrayNode(root->val, false));
			DFS(root->left, serial);
			DFS(root->right, serial);
		}
	}

	TreeNode* constructTree(vector<ArrayNode>& serial, int& rootIndex) {
		// base case, 
		if (serial[rootIndex].isLeaf)	return NULL;

		/*No need to check rootIndex < serial.size(), because assume the input array is correct*/

		// recurse case
		TreeNode* curRoot = new TreeNode(serial[rootIndex].val);
		curRoot->left = constructTree(serial, ++rootIndex);
		curRoot->right = constructTree(serial, ++rootIndex);

		return curRoot;
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

	vector<ArrayNode> serial = codec.serialize(&root);
	for (auto one : serial)
		cout << one;

	TreeNode* reRoot = codec.deserialize(serial);

	system("pause");
	return 0;

}
