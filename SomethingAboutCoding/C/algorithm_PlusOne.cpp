/*
Google Interview Question
LeetCode上的，谷歌面试题，以下是我原创的solution，并不是很难
注意不要把vector中所有元素转换成为int，因为会超出limit

License Key Formatting
You are given a license key represented as a string S which consists only alphanumeric character and dashes. The string is separated into N+1 groups by N dashes.

Given a number K, we would want to reformat the strings such that each group contains exactly K characters, except for the first group which could be shorter than K, but still must contain at least one character. Furthermore, there must be a dash inserted between two groups and all lowercase letters should be converted to uppercase.

Given a non-empty string S and a number K, format the string according to the rules described above.

Example 1:
Input: S = "5F3Z-2e-9-w", K = 4

Output: "5F3Z-2E9W"

Explanation: The string S has been split into two parts, each part has 4 characters.
Note that the two extra dashes are not needed and can be removed.
Example 2:
Input: S = "2-5g-3-J", K = 2

Output: "2-5G-3J"

Explanation: The string S has been split into three parts, each part has 2 characters except the first part as it could be shorter as mentioned above.
Note:
The length of string S will not exceed 12,000, and K is a positive integer.
String S consists only of alphanumerical characters (a-z and/or A-Z and/or 0-9) and dashes(-).
String S is non-empty.
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
	vector<int> plusOne(vector<int>& digits) {
		int size = digits.size();

		// initial check, if the rightmost digit is NOT 9, then ++ and problem solved
		if (digits[size - 1] != 9) {
			digits[size - 1] ++;
			return digits;
		}

		// from here begins the logic when the rightmost digit is 9
		digits[size - 1] = 0;
		bool plus = true;

		// traverse from behind, trying to find a digit that is NOT 9
		for (int i = size - 2; i >= 0 && plus; i--) {
			// found  a digit that is 9, ret to 0 and keep plus equals to TRUE
			if (digits[i] == 9) {
				digits[i] = 0;
			}
			// found a digit that is NOT 9, ++ and problem solved
			else {
				digits[i] ++;
				plus = false;
				break;
			}
		}

		// after the traverse, if plus is still TRUE
		//	need to add 1 at head of vector
		if (plus) {
			digits.insert(digits.begin(), 1);
		}

		return digits;
	}
};
int main() {
	Solution s;
	vector<int> input = { 9,8,7,6,5,4,3,2,1,0 };
	s.plusOne(input);

	system("pause");
	return 0;

}
