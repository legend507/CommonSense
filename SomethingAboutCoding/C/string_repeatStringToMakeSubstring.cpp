/*
Google Interview Questions
Repeated String Match
Given two strings A and B, find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").

Note:
The length of A and B will be between 1 and 10000.
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

class Solution {
public:
	/*以下方法可以解决问题，但是时间复杂度太高...
	ToDo: 找一个比较好的解决方法*/
	bool isSubstring(string& str, string& sub) {
		int sizeStr = str.size();
		int sizeSub = sub.size();
		for (int i = 0; i <= sizeStr-sizeSub; i++) {
			int j = 0; 
			bool notMatch = false;
			while (j < sizeSub) {
				if (str[i + j] != sub[j]) {
					notMatch = true;
					break;
				}
				j++;
			}
			if (notMatch == false)	return true;
		}

		return false;
	}
	int repeatedStringMatch(string A, string B) {
		// 下面这条公式很重要，是for loop的核心思想
		// say repeating A will solve this problem,
		//	then # of repeatation should be max = Bsize/Asize+2
		int sizeA = A.size();
		int sizeB = B.size();
		string repeat;
		for (int i = 0; i <= sizeB / sizeA + 2; i++) {
			repeat += A;
			if (isSubstring(repeat, B))	return i+1;
		}
		return -1;
	}
};

int main() {
	Solution s;
	string A = "aa";
	string B = "cdabcdab";

	s.isSubstring(A, B);

	s.repeatedStringMatch(A, B);

	system("pause");
	return 0;

}
