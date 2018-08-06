/*
Google Interview Q

Given a compressed string in which a number followed by [] indicate how many times those characters occur, decompress the string
Eg. : a3[b2[c1[d]]]e will be decompressed as abcdcdbcdcdbcdcde.
Assume the string is well formed and number will always be followed by a [].
*/

class Solution {
public:
    /*下面的方法是别人的，recursion*/
	string expandStr(string& str) {
		return doRecurse(str, 0);

	}
    /*
    if [, then recurse, with pos + 1,
    if ], end of a recursion, return all in current "[]"
    
    */
	string doRecurse(string& str, int& pos) {
		int num = 0;
		string ret = "";
		for (; pos < str.size(); pos++) {
			// 
			if (str[pos] == '[') {
				string inBrackt = doRecurse(str, ++pos);
				// check num
				for (; num > 0; num--) ret += inBrackt;	// after this, num = 0
			}
			// is a number
			else if ('0' <= str[pos] && str[pos] <= '9') {
				num = num * 10 + str[pos] - '0';
			}
			// when meet a ]
			else if (str[pos] == ']') {
				// for recurse func return
				return ret;
			}
			// is a char
			else {
				ret += str[pos];
			}
		}
		// for final return
		return ret;
	}
};

/*----------- 在google的techdevguide上看到了同样的问题，当时我解出来了 --------------*/
/*
GoogleTechDevGuide Q

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
	/* 我的方法，
	基本想法就是，先找到一对[]，里面只包含char,不包含其他[]
	然后找
	[ 之前的数字，
	数字之前的substr
	]之后的substr
	然后用数字x[]之间的内容，当成一个新的substr
	之后把3个str给concatenate，组成新的string，
	重复，知道找不到[]
	*/
	string process(string& input) {
		string result = input;
		while (result.find('[') != string::npos) {
			int posL = result.find('[');
			int posR;

			// This loop find a [], and NO other [] inside of this pair
			for (int i = posL; i < result.size(); i++) {
				if (result[i] == '[') posL = i;
				if (result[i] == ']') { posR = i; break; }
			}

			// dup= the chars in the []
			string dup = result.substr(posL + 1, posR - posL - 1);
			// rightStr= all string on the right side of the ]
			string rightStr = result.substr(posR + 1, result.size() - posR - 1);

			// find how many times
			int numBoundary;	// 
			for (int i = posL - 1; i >= 0; i--) {
				// reach the 1st char (leftmost), stop
				if (result[i] >= '0' && result[i] <= '9' && i == 0) { numBoundary = 0; break; }
				// move left, as long as current char is 0~9
				if (result[i] >= '0' && result[i] <= '9') continue;
				else { numBoundary = i + 1; break; }
			}
			// 
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
	string input = "a3[b2[c1[d]]]e";
	/*abcdcdbcdcdbcdcde 	*/

	Solution s;
	cout << s.process(input);

	system("pause");
	return 0;
}