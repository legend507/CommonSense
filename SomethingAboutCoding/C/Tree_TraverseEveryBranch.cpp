/*
Google Interview Question
 Given a binary tree, where every node value is a Digit from 1-9 .Find the sum of all the numbers which are formed from root to leaf paths.
 
 For example consider the following Binary Tree.
 
 6
 /      \
 3          5
 /   \          \
 2     5          4
    /   \
    7     4
 There are 4 leaves, hence 4 root to leaf paths:
 Path                    Number
 6->3->2                   632
 6->3->5->7               6357
 6->3->5->4               6354
 6->5>4                    654
 Answer = 632 + 6357 + 6354 + 654 = 13997
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// a structure of TreeNode
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    // constructor
    TreeNode(int x): val(x),left(NULL),right(NULL) {}
};

class Solution {
private:
    vector<int> allBranchNum;
    
    void doRecurse(TreeNode* curRoot, string oneNum) {
        oneNum += to_string(curRoot->val);
        
        // base case
        if(curRoot->left == NULL && curRoot->right == NULL) {
            allBranchNum.push_back(stoi(oneNum));
            return;
        }
        
        // recurse case
        if(curRoot->left != NULL)   doRecurse(curRoot->left, oneNum);
        if(curRoot->right != NULL)  doRecurse(curRoot->right, oneNum);
        return;
    }
public:
    int traverseBinaryTree(TreeNode* root) {
        if(root == NULL)    return 0;
        
        string oneNum;
        doRecurse(root, oneNum);
        
        int ret = 0;
        for(auto oneNum : allBranchNum)
            ret += oneNum;
        
        return ret;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution sol;
    
    TreeNode *root = new TreeNode(6);
    root->left        = new TreeNode(3);
    root->right       = new TreeNode(5);
    root->left->left  = new TreeNode(2);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    
    cout << sol.traverseBinaryTree(root) << endl;
    
    return 0;
}

