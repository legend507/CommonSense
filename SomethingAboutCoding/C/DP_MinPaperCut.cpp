/*
Paper Cut into Minimum Number of Squares | Set 2
Given a paper of size A x B. Task is to cut the paper into squares of any size. Find the minimum number of squares that can be cut from the paper.

Examples:

Input  : 36 x 30
Output : 5
Explanation :
3 (squares of size 12x12) +
2 (squares of size 18x18)

Input  : 4 x 5
Output : 5
Explanation :
1 (squares of size 4x4) +
4 (squares of size 1x1)
Asked in : Google
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
#include <unordered_set>
using namespace std;

class Solution {
public:
	/*
	下面的方法(Greedy Algorithm)是错的！！！
	不能每次都看width来cut，上面的Example 1就是一个例子
	*/
	int paperCut(int x, int y) {
		int len = max(x, y);
		int width = min(x, y);

		return doRecurse(len, width);
	}
	int doRecurse(int len, int width) {
		// base case
		if (len == width)	return 1;

		// recurse case,
		//	got one square (width, width) from current input
		cout << width << ":" << width << endl;
		return 1 + doRecurse(max(len - width, width), min(len - width, width));
	}


	/* 下面的是recursive的DP方法，可以给出正确答案
	Explanation:
	paperCut_dp_recurse is a function which tries to split the rectangle at some position. The function is called recursively for both parts. Try all possible splits and take the one with minimum result. The base case is when both sides are equal i.e the input is already a square, in which case the result is 1. We are trying to find the cut which is nearest to the center which will lead us to our minimum result.
	Assuming we have a rectangle with width is N and height is M.

	1. if (N == M), so it is a square and nothing need to be done.
	2. Otherwise, we can divide the rectangle into two other smaller one (N – x, M) and (x, M), so it can be solved recursively.
	3. Similarly, we can also divide it into (N, M – x) and (N, x)
	*/
	int paperCut_dp_entry(int m, int n) {
		// input check, m, n > 0
		if (m == 0 || n == 0)	return 0;

		const int MAX = 300;	// assume m and n < 300
								/*	dp[m][n] means minimum squares when input is m and n	*/
		vector<vector<int>> dp(MAX, vector<int>(MAX, 0));

		return paperCut_dp_recurse(m, n, dp);
	}
	int paperCut_dp_recurse(int m, int n, vector<vector<int>>& dp) {
		// base case 1
		if (m == n)	return 1;

		// base case 2, if the answer is previous calculated, 
		if (dp[m][n])	return dp[m][n];

		// recurse case
		int vertical_min = INT_MAX;
		int horizontal_min = INT_MAX;
		/*
		The 2 for loops below,
		assume m = horizontal length, n = vertical length
		这两个for就是try每种切法(both horizontally and vertically)，然后给出当前m和n的情况下的最优解	*/
		for (int i = 1; i <= m / 2; i++) {
			horizontal_min = min(
				/*check every possible cut horizontally, cut at i, then we have 2 rect (i, n) and (m-i, n) */
				paperCut_dp_recurse(i, n, dp) + paperCut_dp_recurse(m - i, n, dp),
				horizontal_min);
		}
		for (int j = 1; j <= n / 2; j++) {
			vertical_min = min(
				/*same as above, check every possible cut vertically*/
				paperCut_dp_recurse(m, j, dp) + paperCut_dp_recurse(m, n - j, dp),
				vertical_min);
		}

		/*best case when input is m and n*/
		dp[m][n] = min(vertical_min, horizontal_min);

		return dp[m][n];
	}

};

int main()
{


	vector<int> nums = { 1, 4, 20, 3, 10, 5 };

	Solution s;
	cout << s.paperCut(36, 30);
	cout << s.paperCut_dp_entry(36, 30);

	system("pause");
	return 0;
}

