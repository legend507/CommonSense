/*
Google Interview Qs
Decode Ways
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
	// think s = 11111 <- This is a fucking Fibonaci, with ret = 8
	// think s = 11119 <- This is also a Fibonaci, with ret = 8
	// think s = 111191 <- same as 11119, ret = 8
	int numDecodings(string s) {
		// if size = 0 or first element is 0
		if (!s.size() || s.front() == '0') return 0;

		// ret          : decode ways of s[i]
		// ret_former   : decode ways of s[i-1]
		int ret = 1, ret_former = 1;

		// traverse from s[1], because already made sure s[0] != 0
		for (int i = 1; i < s.size(); i++) {
			// check if is 0
			if (s[i] == '0') {
				ret = 0;
			}

			// then check if former digit is 1 or 2
			// 10 ~ 16, 20~26
			if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
				ret = ret + ret_former;             // now ret <- former ret + ret_former
				ret_former = ret - ret_former;      // now ret_former <- former ret
			}
			// 17, 18, 19
			else {

				// 11001, when reach another valid number after consecutive 0s, ret and ret_former are both 0
				ret_former = ret;
			}
		}
		return ret;
	}
///////////////////////////////////////////////////////////////////////////////
	/*一下是一个dp解法，比上面的容易想一些，*/
	int numDecodings_dp(string s) {
		int size = s.size();
		if (0 == size)	return 0;

		// dp[i] means how many ways to decode for s[0~i-1]
		vector<int> dp(size+1, 0);
		dp[0] = 1;
		dp[1] = ('0' == s[0] ? 0 : 1);	// is s[0] is 0, then s[0] has 0 ways to decode

		for (int i = 2; i <= size; i++) {
			/*
			先想一个具体例子：1，1，2，4， s[i-1]=4的情况下，有几种decode方法？
			解释一下，下面2行就相当于这4种情况
			dp[i] = 0, 当s[i-1] = 0且s[i-2]不是1或2													; s[i-2]&s[i-1] 是3到9个一个数&0，0无法被decode
			dp[i] = dp[i-1], 当s[i-1] ！= 0且 s[i-2] & s[i-1] 不在 10到26的范围时						; s[i-2]&s[i-1] 是2&8或3&9, etc., 只有一种decode方法(s[i-2]&s[i-1] decode成2个char)
			dp[i] = dp[i-2], 当s[i-1] =0 且s[i-2] & s[i-1] 在 10到26的范围时(换句话说s[i-2]为1或2时)	; s[i-2]&s[i-1] 是1&0或2&0, 只有一种decode方法(s[i-2]&s[i-1] decode成1个char)
			dp[i] = dp[i-1] + dp[i-2], 当s[i-1] != 0且 s[i-2] & s[i-1] 在 10到26的范围时				; s[i-2]&s[i-1] 是2&1或1&4， etc., 有2中decode方法(把s[i-2]和s[i-1]分开成2个char，或结合成1个char)
			*/
			dp[i] = ('0' == s[i - 1] ? 0 : dp[i - 1]);	// if s[i-1] is 0, then s[0~i] has same ways as s[0~i-1]; because we must decode s[i-1] with s[i-2] as one char, and s[i] as another
			dp[i] = ('1' == s[i - 2] || ('2' == s[i - 2] && s[i - 1] < '7') ? dp[i] + dp[i - 2] : dp[i]);
		}

		// decode ways for s[0 to size-1]
		return dp[size];
	}

};



int main() {
	Solution s;
	
	system("pause");
	return 0;

}
