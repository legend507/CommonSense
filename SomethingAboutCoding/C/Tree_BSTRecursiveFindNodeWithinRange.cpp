/*
Given a Binary Search Tree (BST) and a range, count number of nodes that lie in the given range.

Examples:

Input:
10
/    \
5       50
/       /  \
1       40   100
Range: [5, 45]

Output:  3
There are three nodes in range, 5, 10 and 40

下面class里写了两个递归方程，一个是我写的
另一个sophi的是参考答案，这个比较好，根据BST的特性少扫描了一些node
*/

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <windows.h>
using namespace std;

// A BST node
struct node
{
	int data;
	node* left, *right;

	node(int x) : data(x), left(NULL), right(NULL) {}
};

class BSTSearch {
private:
	vector<int> allValue;

	int sophisticatedCount(int min, int max, node* curRoot) {
		// base case
		if (!curRoot) return 0;
		if (curRoot->data == min && curRoot->data == max)	return 1;

		// recurse case
		//	1. current data in range
		if (min <= curRoot->data && curRoot->data <= max) {
			allValue.push_back(curRoot->data);
			return 1
				+ sophisticatedCount(min, max, curRoot->left)
				+ sophisticatedCount(min, max, curRoot->right);
		}
		//	2. current value too small, go right branch
		else if (curRoot->data < min)
			return sophisticatedCount(min, max, curRoot->right);
		//	3. current value too large, go left branch
		else
			return sophisticatedCount(min, max, curRoot->left);
	}

	int count(int min, int max, node* curRoot, int& ret) {
		// base case
		if (curRoot == NULL)
			return 0;
		if (curRoot->data >= min && curRoot->data <= max) {
			allValue.push_back(curRoot->data);
			ret++;
		}

		// recurse case	<- can be improved
		count(min, max, curRoot->left, ret);
		count(min, max, curRoot->right, ret);
		return 0;
	}

public:
	int sophisticatedRangeSearch(int min, int max, node* root) {
		return sophisticatedCount(min, max, root);
	}

	int rangeSearch(int min, int max, node* curRoot) {
		int ret = 0;
		count(min, max, curRoot, ret);
		return ret;
	}

	void printAllResult() {
		for (auto oneResult : allValue) {
			cout << oneResult << endl;
		}
	}

};

int main() {
	BSTSearch bsts;

	node *root = new node(10);
	root->left = new node(5);
	root->right = new node(50);
	root->left->left = new node(1);
	root->right->left = new node(40);
	root->right->right = new node(100);

	cout << bsts.sophisticatedRangeSearch(2, 51, root) << endl;;

	bsts.printAllResult();

	system("pause");
	return 0;
}