/*
Google Interview Question
 Given two Binary Search Trees(BST), print the elements of both BSTs in sorted form. The expected time complexity is O(m+n) where m is the number of nodes in first tree and n is the number of nodes in second tree. Maximum allowed auxiliary space is O(height of the first tree + height of the second tree).
 
 Examples:
 
 First BST
 3
 /     \
 1       5
 Second BST
 4
 /   \
 2       6
 Output: 1 2 3 4 5 6
 
 
 First BST
 8
 / \
 2   10
 /
 1
 Second BST
 5
 /
 3
 /
 0
 Output: 0 1 2 3 5 8 10
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
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
    /*
     我需要将两个BST合并成为一个BST，
     第一步应该是Serialize两个BST（把两个BST的元素变成两个vector）
     第二步merge两个vector成为一个vector
     最后将这个vector在deserialize成为一个BST
     */
    
public:
    /*
     主func，Input是两个BST的root，Output是新BST的root
     */
    TreeNode* mergeTwoBST(TreeNode* root1, TreeNode* root2) {
        vector<int> v1;
        BSTToVector_inorder(root1, v1);
        
        vector<int> v2;
        BSTToVector_inorder(root2, v2);
        
        vector<int> v = mergeVector(v1, v2);
        
        return sortedVectorToBST(v);
    }
    
    /*
     将一个BST转换成asending order sorted vector
     Input:     a BST
     Output:    a vector containing all data in the tree (ascending order)
     */
    void BSTToVector_inorder(TreeNode* root, vector<int>& store) {
        if(root == NULL)    return;
        
        // 1st, recur on left
        BSTToVector_inorder(root->left, store);
        
        // store data
        store.push_back(root->val);
        
        // then recur on right
        BSTToVector_inorder(root->right, store);
    }
    
    /*
     注意： 下面两个func用递归的方法从一个 sorted vector 构造一个 balanced BST ^_^
     */
    TreeNode* sortedVectorToBST(vector<int>& v) {
        int vLen = (int)v.size();
        
        TreeNode* root = doRecurse(v, 0, vLen-1);
        
        return root;
    }
    TreeNode* doRecurse(vector<int>& v, int start, int end) {
        // base case
        if(start > end) return NULL;
        
        // recurse case
        int mid = (start + end) /2;
        TreeNode * root = new TreeNode(v[mid]);
        //  1. recurse construct left branch
        root->left = doRecurse(v, start, mid-1);
        //  2. recurse construct right branch
        root->right = doRecurse(v, mid+1, end);
        
        return root;
    }
    
    /*
     将两个ascending order sorted vector合并成一个
     Input:     2 ascending sorted vector1 and vector2
     Output:    a vector, constructed by merging v1 and v2 in ascending order
     */
    vector<int> mergeVector(vector<int>& v1, vector<int>& v2) {
        vector<int> ret;
        int i = 0, j = 0;
        // traverse v1 and v2, construct ret
        while( i < v1.size() && j < v2.size() ) {
            // pick smaller element and put in ret
            if(v1[i] < v2[j]) {
                ret.push_back(v1[i]);
                i++;
            }
            else {
                ret.push_back(v2[j]);
                j++;
            }
        }
        // if element remaining in v1
        while(i < v1.size()) {
            ret.push_back(v1[i]);
            i++;
        }
        // if element remianing in v2
        while(j < v2.size()) {
            ret.push_back(v2[j]);
            j++;
        }
        return ret;
    }
    
    void printInorder(TreeNode* node)
    {
        if (node == NULL)
            return;
        
        /* first recur on left child */
        printInorder(node->left);
        
        cout << node->val << " " << endl;
        
        /* now recur on right child */
        printInorder(node->right);
    }
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution sol;
    
    /* Create following tree as first balanced BST
     100
     /  \
     50    300
     / \
     20  70
     */
    TreeNode *root1     = new TreeNode(100);
    root1->left         = new TreeNode(50);
    root1->right        = new TreeNode(300);
    root1->left->left   = new TreeNode(20);
    root1->left->right  = new TreeNode(70);
    
    /* Create following tree as second balanced BST
     80
     /  \
     40   120
     */
    TreeNode *root2     = new TreeNode(80);
    root2->left         = new TreeNode(40);
    root2->right        = new TreeNode(120);
    
    TreeNode* newTree = sol.mergeTwoBST(root1, root2);
    sol.printInorder(newTree);
    
    return 0;
}
