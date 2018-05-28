/*
Check whether a given string is an interleaving of two other given strings
给3个string，看3rd string是否是由1st和2nd string交错构成的
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
//    TreeNode* left, *right;
//
//    TreeNode(T x) : data(x), left(NULL), right(NULL) {}
//};

struct TreeNode
{
	char data;
	TreeNode* left, *right;

	TreeNode(char x) : data(x), left(NULL), right(NULL) {}
};

class InterleavedString {

public:
	/*
	递归解法，想法就是
	如果str1和str2包含相同char，就分支，用str1的试一下，再用str2的试一下
	O(2^n) in worst case
	*/
	bool isInterleaved_1(string str1, string str2, string str3) {
		int str1Idx = 0;
		int str2Idx = 0;
		int str3Idx = 0;

		return recurseCheck(str1, str2, str3, str1Idx, str2Idx, str3Idx);
	}
	bool recurseCheck(string& str1, string& str2, string& str3, int str1Idx, int str2Idx, int str3Idx) {
		// base case - if all 3 strings reach end at the same time
		if (str1Idx == str1.size()
			&& str2Idx == str2.size()
			&& str3Idx == str3.size()) {
			return true;
		}
		// base case - if str3 reaches end, while other two are not
		if (str3Idx == str3.size())
			return false;

		// recurse case
		//	if str3和str1的当前char相同，
		//	if str3和str2的当前char相同
		//	if str1和str2中找不到和str3当前char相同的，直接返回false
		return (
			(str3[str3Idx] == str1[str1Idx] && recurseCheck(str1, str2, str3, str1Idx + 1, str2Idx, str3Idx + 1))		// check if a char in str1 is equal to current char in str3
			|| (str3[str3Idx] == str2[str2Idx] && recurseCheck(str1, str2, str3, str1Idx, str2Idx + 1, str3Idx + 1))	// check if a char in str2 is equal to current char in str3
			);
	}

	/*=============================================================================================================================================*/

	/*
	Dynamic Programming
	学一下DP matrix的代表意义
	*/
	bool isInterleaved_2(string str1, string str2, string str3) {
		int str1Len = str1.size();
		int str2Len = str2.size();

		// dp[i][j] = true, if str3[0...i+j-1] is a interleaved of str1[0...i-1] and str2[0...j-1]
		//	return dp[str1Len][str2Len]
		vector<vector<bool>> dp(str1Len + 1, vector<bool>(str2Len + 1, false));

		/*
		case 1: dp[0][0] = true, all 3 string empty
		case 2: dp[0][j] = dp[0][j-1], if str3[j-1] == str2[j-1], 如果str1为空，则只需看str2和str3当前char是否相同，如果相同则看前一char
		case 3: dp[i][0] = dp[i-1][0], if str3[i-1] == str1[i-1], 如果str2为空
		- 一下case比较复杂...
		case 4: 如果str3当前char和str1相同，但和str2不同，dp[i][j] = dp[i-1][j]
		case 5: 如果str3当前char和str2相同，但和str1不同，dp[i][j] = dp[i][j-1]
		case 6: 如果str3当前char和str1以及str2都相同，则看 dp[i][j] = dp[i-1][j] || dp[i][j-1], 有一个为True就为True
		*/
		// case 1
		dp[0][0] = true;

		for (int i = 0; i <= str1Len; i++) {
			for (int j = 1; j <= str2Len; j++) {

				// case 2
				if (i == 0) {
					if (str3[j - 1] == str2[j - 1]) dp[0][j] = dp[0][j - 1];
				}
				// case 3
				else if (j == 0) {
					if (str3[i - 1] == str1[i - 1])dp[i][0] = dp[i - 1][0];
				}
				// case 4 - from now on, current char in str3 means str3[i+j-1]
				else if (str3[i + j - 1] == str1[i - 1]
					&& str3[i + j - 1] != str2[j - 1])	dp[i][j] = dp[i - 1][j];

				// case 5
				else if (str3[i + j - 1] == str2[j - 1]
					&& str3[i + j - 1] != str1[i - 1])	dp[i][j] = dp[i][j - 1];

				// case 6
				else if (str3[i + j - 1] == str1[i - 1]
					&& str3[i + j - 1] == str2[j - 1])	dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
			}
		}
		return dp[str1Len][str2Len];
	}
};


int main() {
	string str1 = "XXY";
	string str2 = "XXxZ";

	string str3 = "XXxZXXY";

	InterleavedString is;

	if (is.isInterleaved_2(str1, str2, str3))
		cout << "YES";
	else
		cout << "NO";

	system("pause");
	return 0;
}

