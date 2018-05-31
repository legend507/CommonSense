/*
Google Interview Question

Given two strings s and t, determine if they are both one edit distance apart.

Note:

There are 3 possiblities to satisify one edit distance apart:

Insert a character into s to get t
Delete a character from s to get t
Replace a character of s to get t
Example 1:

Input: s = "ab", t = "acb"
Output: true
Explanation: We can insert 'c' into s to get t.
Example 2:

Input: s = "cab", t = "ad"
Output: false
Explanation: We cannot get t from s by only one step.
Example 3:

Input: s = "1203", t = "1213"
Output: true
Explanation: We can replace '0' with '1' to get t.
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
	/*
	以下solution是我原创，beat50%左右，还是不太理想
	问题挺简单，就是根据s，t长度判断是需要 insert/delete/replace中的哪个，然后分别判断
	*/
	bool isOneEditDistance(string s, string t) {
		if (s == t) return false;
		int sizeS = s.size();	// modify s, to make it identical to t
		int sizeT = t.size();	// 

		if (abs(sizeS - sizeT) > 1) return false;

		// insert
		if (sizeS + 1 == sizeT) {
			int si = 0;
			int ti = 0;
			bool foundOne = false;
			while (si < sizeS && ti < sizeT) {
				if (s[si] != t[ti]) {
					si--;
					if (foundOne) return false;
					else foundOne = true;
				}
				si++; ti++;
			}
			return true;
		}
		// delete
		else if (sizeS - 1 == sizeT) {
			int si = 0;
			int ti = 0;
			bool foundOne = false;
			while (si < sizeS && ti < sizeT) {
				if (s[si] != t[ti]) {
					ti--;
					if (foundOne) return false;
					else foundOne = true;
				}
				si++; ti++;
			}
			return true;
		}
		// replace
		else {
			int si = 0;
			int ti = 0;
			bool foundOne = false;
			while (si < sizeS && ti < sizeT) {
				if (s[si] != t[ti]) {
					if (foundOne) return false;
					else foundOne = true;
				}
				si++; ti++;
			}
			return true;
		}
	}
};

int main() {
	Solution s;

	s.isOneEditDistance("ab", "acb");

	system("pause");
	return 0;

}
