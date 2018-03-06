/*
 Given an array of distinct elements. The task is to find triplets in array whose sum is zero.
 
 Examples:
 
 Input : arr[] = {0, -1, 2, -3, 1}
 Output : 0 -1 1
 2 -3 1
 
 Input : arr[] = {1, -2, 1, 0, 5}
 Output : 1 -2  1
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>
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
public:
    void findZeroSumTriple(vector<int>& input) {
        int len = (int)input.size();
        
        sort(input.begin(), input.end());
        for(int i1 = 0; i1<len-2; i1++) {
            int i2 = i1+1;      //
            int i3 = len-1;
            
            while(i2 < i3) {
                int result = input[i1] + input[i2] + input[i3];
                if(result == 0) {
                    cout << input[i1] << "+" << input[i2] << "+" << input[i3] << "== 0" << endl;
                    break;
                }
                else if(result > 0)  i3 --;
                else    i2++;
            }
        }
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution sol;
    vector<int> input = {0, -1, 2, -3, 1};
    
    sol.findZeroSumTriple(input);
    
    return 0;
}
