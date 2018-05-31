/*
Google Interview Question

Valid Parentheses
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true
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
	以下是我自己的solution，beat 95%，感觉还行
	关于brackets和Parentheses的问题，要想到用stack
	*/
	bool isValid(string s) {
		int size = s.size();
		if (size == 0)	return true;
		stack<char> opens;

		for (int i = 0; i < size; i++) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{') opens.push(s[i]);

			else {
				if (!opens.empty() && s[i] == ')' && opens.top() == '(') opens.pop();
				else if (!opens.empty() && s[i] == ']' && opens.top() == '[') opens.pop();
				else if (!opens.empty() && s[i] == '}' && opens.top() == '{') opens.pop();
				else return false;
			}
		}

		if (opens.empty())	return true;
		else				return false;
	}
};

int main() {
	Solution s;


	system("pause");
	return 0;

}
