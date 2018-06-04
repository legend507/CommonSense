/*
Inorder Successor in BST
  Go to Discuss
Given a binary search tree and a node in it, find the in-order successor of that node in the BST.

Note: If the given node has no in-order successor in the tree, return null.

Example 1:

Input: root = [2,1,3], p = 1

  2
 / \
1   3

Output: 2
Example 2:

Input: root = [5,3,6,2,4,null,null,1], p = 6

      5
     / \
    3   6
   / \
  2   4
 /   
1

Output: null
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    bool found = false;
    TreeNode* ret = NULL;
public:
    /*下面方法是我自己的，beat 50%左右，*/
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        
        doRecurse(root, p);
        
        return ret;
        
    }
    /*首先，先把DFS inorder的code写出来，然后在改*/
    void doRecurse(TreeNode* root, TreeNode* p) {
        // base case
        if(root == NULL) return;
        if(ret != NULL) return;
        
        // recurse case
        doRecurse(root->left, p);
        
        if(!found) {
            if(root->val == p->val) found = true;
        } else {
            if(ret == NULL) ret = root;
            else return;
        }
        
        doRecurse(root->right, p);
    }
};
