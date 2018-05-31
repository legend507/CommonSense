/*
Google Interview Question

Longest Substring with At Most K Distinct Characters
Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.
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
	以下方法是我原创的，不过效率不高，LeetCode上只beat了不到30%
	以下方法每次要看unique.size, 所以效率不高，

	*/
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		if (k == 0)	return 0;

		int size = s.size();
		if (size <= k)	return size;

		unordered_map<char, int> unique;
		int l = 0;
		int r = 0;
		int maxLen = -1;

		for (int r = 0; r < size; r++) {
			unique[s[r]] ++;
			// found k unique 
			if (unique.size() == k) {
				maxLen = max(maxLen, r - l + 1);
			}
			// one more, need to eliminate
			else if (unique.size() == k + 1) {
				while (unique.size() == k + 1) {
					unique[s[l]] --;
					if (unique[s[l]] == 0) unique.erase(s[l]);	// unique.size() should be k now
					l++;
				}
			}
		}
		return maxLen==-1?size:maxLen;
	}
	/*
	以下方法是别人的，和我的想法差不多，但是胜在判断方法
	应该用一个vector(size=128)来记录出现char，并且递减k来记录出现了几个unique char；最后k==0时，记录长度
	k<0时，出现的unique char太多了，移动begin来把k恢复到0
	e.g., if(vec[s[end]]++==0) k--;
	*/
	int lengthOfLongestSubstringKDistinct_fast(string s, int k) {
		vector<int> map(128, 0);
		int begin = 0, end = 0; //two pointers, one point to tail and one  head
		int d = INT_MIN; //the length of substring
		int len = s.length();
		if (len == 0 || k == 0)
			return 0;

		while (end<len) {
			if (map[s[end]]++ == 0) {
				k--;
				while (k<0 && begin<end) {
					if (--map[s[begin++]] == 0)
						k++;
				}
			}
			end++;
			if (k == 0)
				d = d>(end - begin) ? d : (end - begin);
		}
		return d == INT_MIN ? s.length() : d;
	}
};

int main() {
	Solution s;

	unordered_map<char, int> unique;
	unique['a'] = 0;
	unique.erase('a');
	cout << unique.size(); 

	system("pause");
	return 0;

}
