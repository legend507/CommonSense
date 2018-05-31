/*
Google Interview Questions
Next Closest Time
Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

Example 1:

Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
*/
#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
#include	<set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	string nextClosestTime(string time) {
		// Get all the digit chars and also mininum char.
		set<char> char_set;
		char min_char('9');
		for (char c : time) {
			if (c != ':') {
				char_set.insert(c);
				min_char = std::min(min_char, c);
			}
		}

		// 想法是，从time的后向前看，找到一个digit，把那个digit增大，然后从那个digit之后的数都设定成最小取值(min_char)
		// From back to front, let's try to increase a char 
		// to its next greater char in current digits.
		for (int n = time.size(), i = n - 1; i >= 0; --i) {
			if (time[i] == ':') continue;
			// How upper_bound works: if char_set = 1,3,4,9, and time[i]=3, then the iter points to 4
			auto iter = upper_bound(char_set.begin(), char_set.end(), time[i]);

			/*Following lines are continue conditions (invalid time)*/
			// No greater char
			if (iter == char_set.end()) continue;
			// First digit can't >= '3', first digit means ?3:59
			if (i == 0 && *iter >= '3') continue;
			// Avoid HH >= 24, what about "24:00"? It will never happen
			// when the four digits are "0, 2, 4". Meaning 1?:59 and 2?:59, when 2, the ? can only be 0,1,2,3
			if (i == 1 && time[0] == '2' && *iter >= '4') continue;
			// Avoid ss >= "60", 23:?9, the ? can only be 0,1,2,3,4,5
			if (i == 3 && *iter >= '6') continue;

			// Right now we can increase one digit, set all the 
			// digits behand it as minimum char.
			time[i] = *iter;
			for (int j = i + 1; j < n; ++j) {
				if (time[j] != ':') time[j] = min_char;
			}
			return time;
		}

		// Will reach here only when we can't increase any digit.
		// Then go to the next day and set all the digits with the minimum digit.
		for (char &c : time) {
			if (c != ':') {
				c = min_char;
			}
		}

		return time;
	}
};

int main() {
	string time = "19:44";
	Solution s;
	cout << s.nextClosestTime(time);

	
	system("pause");
	return 0;

}
