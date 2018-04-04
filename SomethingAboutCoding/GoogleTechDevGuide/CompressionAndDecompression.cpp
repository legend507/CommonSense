/*
In this exercise, you're going to decompress a compressed string.

Your input is a compressed string of the format number[string] and the decompressed output form should be the string written number times. For example:

The input

3[abc]4[ab]c

Would be output as

abcabcabcababababc
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
using namespace std;

class Solution {
	string multiDup(string dup, int times) {
		string ret;
		for (int i = 0; i < times; i++) {
			ret += dup;
		}
		return ret;
	}
public:
	string process(string& input) {
		string result = input;
		while (result.find('[') != string::npos) {
			int posL = result.find('[');
			int posR;
			for (int i = posL; i < result.size(); i++) {
				if (result[i] == '[') posL = i;
				if (result[i] == ']') { posR = i; break; }
			}

			string dup = result.substr(posL + 1, posR - posL - 1);
			string rightStr = result.substr(posR + 1, result.size() - posR - 1);

			// find how many times
			int numBoundary;
			for (int i = posL - 1; i >= 0; i--) {
				if (result[i] >= '0' && result[i] <= '9' && i == 0) { numBoundary = 0; break; }
				if (result[i] >= '0' && result[i] <= '9') continue;
				else { numBoundary = i + 1; break; }
			}
			int times = stoi(result.substr(numBoundary, posL - numBoundary));
			string leftStr = result.substr(0, numBoundary);

			dup = multiDup(dup, times);

			result = leftStr + dup + rightStr;
		}

		return result;
	}
};

int main()
{
	string input = "3[abc]4[ab]c";

	Solution s;
	cout << s.process(input);

	system("pause");
	return 0;
}