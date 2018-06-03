/*
问题1
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
			//	move head的最终结果小还是move tail的最终结果小？需要两个都试一下
			minInsertion = min(
				doRecurse(str, head + 1, tail),	/*insert in tail the same char as str[head]*/
				doRecurse(str, head, tail - 1)	/*insert in head the same char as str[tail]*/
			) + 1;	// 
		}
		return minInsertion;
	}

	/*
	Method2, DP, 这个方法是错的！！！
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

////////////////////////////////////////////////////////////////////////////////////
/*
问题2
Google Interview Question

Longest Palindromic Substring
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"
*/
#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
#include	<algorithm>
#include	<set>
using namespace std;

class Solution {
public:
	/*以下方法是别人的，很brilliant
	思想是，loop i 从0到size-1,
	对每个i，设定left和right=i，然后先move r跳过所有重复的char，然后
	如果s[left]==s[right]，则left--且right++ 来扩大当前回文substring*/
	string longestPalindrome(string s) {
		int size = s.size();
		if (size == 0) return "";
		if (size == 1) return s;

		int maxLen = 1;
		int maxStart = 0;
		for (int i = 0; i < size; ) {
			// remaining chars not enough to be the longest, break loop
			if (size - i <= maxLen / 2) break;

			int l = i, r = i;

			while (r < size - 1 && s[r + 1] == s[r]) r++;	// think abbbbbbba (7 bs) and abbbbbba (6 bs) are all Palindromic, keep l to 1st a, and move r to 2nd a, and l-- r++ from there.
			i = r + 1;	// reset i, 

			// expand by moving l to left and r to right
			while (r < size - 1 && l > 0 && s[r + 1] == s[l - 1]) { r++; l--; }

			int newLen = r - l + 1;
			if (newLen > maxLen) {
				maxLen = newLen;
				maxStart = l;
			}
		}
		return s.substr(maxStart, maxLen);
	}
};

////////////////////////////////////////////////////////////////////////
/*
问题3
Google Interview Qs

Shortest Palindrome
Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"
*/

#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
#include	<sstream>			// istringstream and ostringstream
#include	<set>
#include	<climits>
#include	<algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////
class Solution {
public:
	/*下面方法是别人的，
	想法很简单 但同时很brilliant，就是创建一个逆序的t，然后找出最短的substr*/
	string shortestPalindrome(string s) {
		string t = s;	// copy the string
		reverse(t.begin(), t.end() );

		int start = 0;
		int len = s.size();

		/*
		Think abcde, edcba
		the while loop will decide to put edcb infront of abcde
		becuase when start = 4, len = 1, a in edcba will equal to a in abcde, break the loop
		*/
		while (t.substr(start, len) != s.substr(0, len)) {
			start++, len--;
		}
		return t.substr(0, start) + s;
	}
};

int main() {
	Solution s;
	string str = "aabba";

	s.shortestPalindrome(str);


	system("pause");
	return 0;
}