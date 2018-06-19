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