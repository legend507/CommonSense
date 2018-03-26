/*
Given a string, find the minimum number of characters to be inserted to convert it to palindrome (回文).

Before we go further, let us understand with few examples:
ab: Number of insertions required is 1. bab
aa: Number of insertions required is 0. aa
abcd: Number of insertions required is 3. dcbabcd
abcda: Number of insertions required is 2. adcbcda which is same as number of insertions in the substring bcd(Why?).
abcde: Number of insertions required is 4. edcbabcde
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

class PalindromeMaker {
public:
	/*
	Method1, 递归
	下面func返回 将入力str变成回文的最小插入回数
	*/
	int findMinInsertion(string str) {
		// 2 pointers, one at head, one at tail
		int head = 0;
		int tail = str.size() - 1;

		return doRecurse(str, head, tail);
	}

	int doRecurse(string& str, int head, int tail) {
		// base case
		if (head > tail)	return INT_MAX;	// abnormal
		if (head == tail)	return 0;	// only have one char
		if (head == tail - 1)	return(str[head] == str[tail] ? 0 : 1);	// have 2 chars

																		// recurse case
		int minInsertion;
		//	check if str[head] == str[tail]
		if (str[head] == str[tail]) {
			// if same char, 0 insertion, move both pointer to middle by 1
			minInsertion = doRecurse(str, head + 1, tail - 1);
		}
		else {
			// if not same, need 1 insertion, move either pointer to middle by 1
			minInsertion = min(
				doRecurse(str, head + 1, tail),	/*insert in tail the same char as str[head]*/
				doRecurse(str, head, tail - 1)	/*insert in head the same char as str[tail]*/
			) + 1;	// 
		}
		return minInsertion;
	}

	/*
	Method2, DP
	O(n^2)
	*/
	int findMinInsertion2(string str) {
		int len = str.size();

		// dp[i][j] = min insertion for str[i~j]
		vector<vector<int>> dp(len, vector<int>(len, 0));
		/*
		case 0: if i > j, dp[i][j] = MAXs
		case 1: if i == j, dp[i][j] = 0
		case 2: if i == j-1, dp[i][j] = 0 (if str[i] == str[j]) or 1 (if str[i] != str[j])
		case 3: if str[i] != str[j], dp[i][j] = min(dp[i+1][j], dp[i][j-1])+1
		if str[i] == str[j], dp[i][j] = dp[i+1][j-1]
		*/
		/*
		注意，以上的想法是错误的！！
		应该以gap的想法，看一下str的头和尾相差多少
		*/

		for (int gap = 1; gap < len; gap++) {
			// loop using gap length, 
			//	fixed distance between i and j
			for (int i = 0, j = gap; j < len; i++, j++) {
				if (str[i] == str[j])  dp[i][j] = dp[i + 1][j - 1];
				else dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
			}
		}
		return dp[0][len - 1];
	}
};

int main() {
	PalindromeMaker bm;
	cout << bm.findMinInsertion2("geeks");

	system("pause");
	return 0;
}

