/*
Google Interview Qs
就是问老式的电话键盘，按两个数字，有多少种可能组合

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.



Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:

Although the above answer is in lexicographical order, your answer could be in any order you want.
*/

class Solution {
    /*下面的方法是我的，*/
public:
	vector<string> letterCombinations(string digits) {
		int len = digits.size();
        if(len == 0) return vector<string>()={};
		vector<string> ret;

		unordered_map<char, string> mapping;
		mapping['2'] = "abc";
		mapping['3'] = "def";
		mapping['4'] = "ghi";
		mapping['5'] = "jkl";
		mapping['6'] = "mno";
		mapping['7'] = "pqrs";
		mapping['8'] = "tuv";
		mapping['9'] = "wxyz";

		vector<int> idx(len, 0);
		while (1) {
			string oneResult;
            // 根据当前的idx vector，construct一个result，然后push进ret里面
			for (int i = 0; i < len; i++) {
				oneResult += mapping[digits[i]][idx[i]];
			}
			ret.push_back(oneResult);
            // 只++最后一个idx
			idx[len - 1] ++;
            // 然后根据最后一个idx的值，决定前面的idx值时候需要进位或者reset to 0
			for (int i = len - 1; i >= 1; i--) {
				if (idx[i] == mapping[digits[i]].size()) {
					idx[i] = 0;
					idx[i - 1] ++;
				}
			}
			if (idx[0] == mapping[digits[0]].size()) break;

		}
		return ret;
	}
};