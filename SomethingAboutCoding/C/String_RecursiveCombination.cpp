/*
The following code generates all combinations of all char in an input string
e.g., if input is "abcd", then the output is
			a
			ab
			abc
			abcd
			abd
			ac
			acd
			ad
			b
			bc
			bcd
			bd
			c
			cd
			d
*/

#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<sstream>			// istringstream and ostringstream
#include	<set>
#include	<climits>
#include	<algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////
class Solution {
public:
	vector<string> stringCombination(string str) {
		vector<string> result;
		string oneResult;

		recurseCombine(oneResult, result, str, 0);

		return result;
	}
private:
	void recurseCombine(
		string oneResult,
		vector<string> & result,
		string & str,
		int start
	) {

		for (int i = start; i < str.size(); i++) {
			oneResult += str[i];
			result.push_back(oneResult);

			recurseCombine(oneResult, result, str, i + 1 /*start*/);
			oneResult = oneResult.substr(0, oneResult.size() - 1);
		}
	}

};

int main() {
	string str = "abcd";

	Solution sol;
	vector<string> result;

	result = sol.stringCombination(str);

	for (auto oneResult : result) {
		cout << oneResult << endl;
	}

	system("pause");
	return 0;
}
