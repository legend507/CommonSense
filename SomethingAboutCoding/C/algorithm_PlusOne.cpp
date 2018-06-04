/*
Google Interview Question
LeetCode上的，谷歌面试题，以下是我原创的solution，并不是很难
注意不要把vector中所有元素转换成为int，因为会超出limit

Plus One
  Go to Discuss
Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:

Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Example 2:

Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
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
