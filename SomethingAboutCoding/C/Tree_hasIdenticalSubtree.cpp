/*
下面的Class可以check
1. 两个Tree是否完全相同
2. 一个Tree是否是另一个Tree的Subtree
3. 一个Tree中是否包含相同subtree	<- Google Interview Question
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

// A BST node
//template <typename T>
//struct TreeNode
//{
//    T data;
//	TreeNode* left, *right;
//    
//	TreeNode(T x) : data(x), left(NULL), right(NULL) {}
//};

struct TreeNode
{
	char data;
	TreeNode* left, *right;

	TreeNode(char x) : data(x), left(NULL), right(NULL) {}
};

class TreeChecker {
	/*
	this class provide a way to check 
		if two trees are identical
		if one tree is a subtree of another
	*/

public:
	/*
	Recursively check if two trees are identical
	*/
	bool areIdentical(TreeNode* root1, TreeNode* root2) {
		// base case
		if (root1 == NULL && root2 == NULL)	return true;
		if (root1 == NULL || root2 == NULL) return false;

		// recurse case
		//	check if data of both root & data of right child & data of left child are the same
		return (
			root1->data == root2->data
			&& areIdentical(root1->left, root2->left)
			&& areIdentical(root1->right, root2->right)
			);
	}

	/*
	check if smallT is a subtree of bigT
	*/
	bool isSubtree(TreeNode* bigT, TreeNode* smallT) {
		// base case
		if (smallT == NULL)	return true;
		if (bigT == NULL) return false;

		if (areIdentical(bigT, smallT))	return true;

		// recurse case
		return (
			isSubtree(bigT->left, smallT)
			|| isSubtree(bigT->right, smallT)
			);
	}

	/*
	Does a tree contains identical subtrees (size of subtree >= 2)?
	subtree的定义是，从tree的某一点开始，到所有leaf为止；并非任取tree的一段
	e.g.,
	Input :  Binary Tree 
               A
             /    \ 
           B        C
         /   \       \    
        D     E       B     
                     /  \    
                    D    E
	Output : Yes
	*/
	// 下面的func，如果有identical subtree，则返回“”，如果没有；则返回tree的serial （e.g., ABD$$E$$C$BD$$ES$$$）
	string hasIdenticalSubtree(TreeNode* root) {
		unordered_set<string> subtrees;

		return hasIdenticalSubtreeUtil(root, subtrees);
	}
	string hasIdenticalSubtreeUtil(TreeNode* root, unordered_set<string>& subtrees) {
		string s = "";

		// base case
		if (root == NULL)	return (s + "$");
		
		// recurse case
		string leftStr = hasIdenticalSubtreeUtil(root->left, subtrees);
		if (leftStr.compare(s) == 0)	return s;
		string rightStr = hasIdenticalSubtreeUtil(root->right, subtrees);
		if (rightStr.compare(s) == 0)	return s;

		s = s + root->data + leftStr + rightStr;

		// store all subtrees in subtrees hashtable, paramete 3 means a signle node (e.g., A$$) is not a subtree
		// 从下到上，存储所有serialized substree string，检查现在的Unordered_set中 已经存储过相同string
		if (s.length() > 3
			&& subtrees.find(s) != subtrees.end())
			return "";

		cout << s << endl;

		// 存储这个tree的所有subtree
		subtrees.insert(s);

		return s;
	}
};


int main() {
	TreeNode *root = new TreeNode('A');
	root->left = new TreeNode('B');
	root->right = new TreeNode('C');
	root->left->left = new TreeNode('D');
	root->left->right = new TreeNode('E');
	root->right->right = new TreeNode('B');
	root->right->right->right = new TreeNode('E');
	root->right->right->left = new TreeNode('D');

	root->right->right->right->left = new TreeNode('S');

	TreeChecker tc;
	cout << "---" << tc.hasIdenticalSubtree(root);

	system("pause");
    return 0;
}
