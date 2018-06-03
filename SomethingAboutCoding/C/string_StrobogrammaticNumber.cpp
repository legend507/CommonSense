/*
Google Interview Qs

Strobogrammatic Number II
Go to Discuss
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

Example:

Input:  n = 2
Output: ["11","69","88","96"]
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <stack>
#include <map>
using namespace std;

class Solution {
public:
	/*以下方法是别人的, beat 98%
	想法挺简单的，就是先创建一个长为n的string(combination)
	然后用两个指针left，right，往中间走
	这个方法看懂了挺简单，很brilliant*/
	vector<string> findStrobogrammatic(int n) {
		if (n == 0) return vector<string>() = { "" };
		if (n == 1) return vector<string>() = { "0", "1", "8" };

		// enumeration, only the following combinations
		map<char, char> reversible;
		reversible['0'] = '0';
		reversible['1'] = '1';
		reversible['6'] = '9';
		reversible['8'] = '8';
		reversible['9'] = '6';

		vector<string> ret;
		string combination(n, '0');
		// 下面的递归函数用两个指针，left和right，依次向中间移动 
		create_combination(reversible, ret, combination, 0, n - 1);

		return ret;
	}
	void create_combination(const map<char, char>& reversible,
		vector<string>& result,
		string& combination,
		int left, int right) {

		// base case
		if (left > right) {
			result.push_back(combination);
			return;
		}

		// recurse case
		//	traverse all 5 possibilities, 
		for (auto oneEle : reversible) {
			// first digit can NOT be 0；制约1
			if (left == 0 && oneEle.first == '0')	continue;

			// only 1, 0, 8 can be in center; when left=right, meaning n is odd；制约2
			//	如果不是0或1或8，试下一个possibility
			if (left == right
				&& oneEle.first != '0'
				&& oneEle.first != '1'
				&& oneEle.first != '8')	continue;


			combination[left] = oneEle.first;
			combination[right] = oneEle.second;
			create_combination(reversible,
				result,
				combination,
				left + 1,
				right - 1);

		}
	}

};

int main() {
	Solution s;
	vector<string> ret = s.findStrobogrammatic(4);

	for (auto one : ret) cout << one << endl;

	system("pause");
	return 0;

}
