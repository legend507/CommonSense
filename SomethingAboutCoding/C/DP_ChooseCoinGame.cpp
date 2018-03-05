/*
 Problem statement: Consider a row of n coins of values v1 . . . vn, where n is even. We play a game against an opponent by alternating turns. In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the value of the coin. Determine the maximum possible amount of money we can definitely win if we move first.
 
 Note: The opponent is as clever as the user.
 
 Let us understand the problem with few examples:
 
 1. 5, 3, 7, 10 : The user collects maximum value as 15(10 + 5)
 
 2. 8, 15, 3, 7 : The user collects maximum value as 22(7 + 15)
 
 Does choosing the best at each move give an optimal solution?
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
    /*
     分析：
        我可以选 ith or jth coin，
        然后对手选（i+1）th or （j-1）th coin
        对手的目的是：？
     解法：
        令dp[i][j]=我可以从ith coin到jth coin得到分数的最大值
        如果给定i，j，则我可以拿到的最大值是
                    max(
                        vi+min( dp[i+2][j], dp[i+1][j-1] ),     <- 我选i，则我的对手就要从i+1和j中选一个。如果对手选i+1，我下次就只能选i+2或j；如果对手选j，我下次就只能选i+1或j-1    (不要想对手会选啥，我只需要确保我自己能拿到最多就好)
                        vj+min( dp[i+1][j-1], dp[i][j-2] )      <- 我选j，则我的对手就要从i和j-1中选一个，
                    )
                    思考一下为什么这里有2个min？
        对于matrix dp的base case：
            i==j时，dp[i][j] = vi
            j==i+1时，dp[i][j] = max(vi, vj)
     */
    int perfectGame(vector<int>& coins) {
        int n = (int)coins.size();
        vector<vector<int>> dp(n, vector<int>(n,0));
        
        for(int i = 0; i < n; i++)      dp[i][i] = coins[i];                        // base case i==j
        for(int i = 0; i < n-1; i++)    dp[i][i+1] = max(coins[i], coins[i+1]);     // base case j==i+1
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                // meaningless when j < i
                if(j<i)     continue;
                
                // base case
                if(j==i)    continue;
                if(j==i+1)  continue;
                
                //
                dp[i][j]    = max(
                    coins[i] + min(dp[i+2][j], dp[i+1][j-1]),
                    coins[j] + min(dp[i+1][j-1], dp[i][j-2])
                );
            }
        }
        return dp[0][n-1];
    }
    
};


int main(int argc, const char * argv[]) {
    // insert code here...
    Solution sol;
    vector<int> input = {8, 15, 3, 7};
    
    cout << sol.perfectGame(input) << endl;
    
    return 0;
}
