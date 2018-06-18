/*
Google Interview Question
Given two strings, the task is to check whether these strings are meta strings or not. Meta strings are the strings which can be made equal by exactly one swap in any of the strings. Equal string are not considered here as Meta strings.

Examples:

Input : A = "geeks" 
        B = "keegs"
Output : 1
By just swapping 'k' and 'g' in any of string, 
both will become same.

Input : A = "rsting"
        B = "string
Output : 0

*/
#include    <string>
#include    <iostream>
#include    <list>
using namespace std;

class MetaStringChecker {
public:
	// return:
	//  -1 = str1 and str2 can not be swap to the same
	//  other = how many swaps needed to make str1 and str2 equal
	int howManySwap(string& str1, string& str2) {
		int str1Len = str1.size();
		int str2Len = str2.size();
		if (str1Len != str2Len)  return -1;  // length different, swap won't solve this problem

		list<int> record;
		int swapCounter = 0;

		/*
		下面的Loop是在遍历整个string，
		如果找到一个位置i不同，
		则决定放不放到record中，
		如果现在的record中已经有一个pos能和i对应，则不放i，同时把那个pos从record中移除
		如果在record中找不到这个pos，则把i放入record中*/
		for (int i = 0; i < str1Len; i++) {
			if (str1[i] != str2[i]) {
				// try to find this (str2[i],str1[i]) pair in list,
				//  if found, swapCounter ++
				//  if NOT found, insert into list
				bool found = false;
				for (auto itr = record.begin(); itr != record.end(); itr++) {
					if (str1[*itr] == str2[i] && str1[i] == str2[*itr]) {
						found = true;
						record.erase(itr);	// this line erase a char == str2[i] that is found before
						break;
					}
				}
				if (found)
					swapCounter++;
				else
					record.push_back(i);	// if not found, push this i (str1[i]) into list, and may be it will be used afterward
			}
		}

		if (record.size() != 0)
			return -1;
		else
			return swapCounter;
	}
};

int main() {
	MetaStringChecker msc;

	string s1 = "geeks";
	string s2 = "keegs";

	string s3 = "string";
	string s4 = "trsing";

	cout << msc.howManySwap(s1, s2) << endl;
	cout << msc.howManySwap(s3, s4) << endl;

	system("pause");
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
/*
下面的问题和上面的有些像，不过更难，
试问最少要swap A中的char几次，才能使A==B?
Strings A and B are K-similar (for some non-negative integer K) if we can swap the positions of two letters in A exactly K times so that the resulting string equals B.

Given two anagrams A and B, return the smallest K for which A and B are K-similar.

Example 1:

Input: A = "ab", B = "ba"
Output: 1
Example 2:

Input: A = "abc", B = "bca"
Output: 2
Example 3:

Input: A = "abac", B = "baca"
Output: 2
Example 4:

Input: A = "aabc", B = "abca"
Output: 2
Note:

1 <= A.length == B.length <= 20
A and B contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}
*/

class Solution {
public:
	/*下面的方法是别人的，没太看懂...*/
    int kSimilarity(string A, string B) {
        string tA, tB;
        for (int i =  0; i < A.size(); i++) {
            if (A[i] != B[i]) {
                tA.push_back(A[i]);
                tB.push_back(B[i]);
            }
        }
        unordered_map<string, int> dp;
        return dfs(tA, tB, 0, dp);
    }
    
    int dfs(string a, string b, int pos, unordered_map<string, int>& dp) {
        if (pos == b.size()) {
            dp[a] = 0;
            return 0;
        }
        if (dp.count(a)) return dp[a];
        if (a[pos] == b[pos]) return dfs(a, b, pos+1, dp);
        int mn = INT_MAX;
        for (int i = pos + 1; i < a.size(); i++) {
            if (a[i] == b[pos]) {
                swap(a[pos], a[i]);
                mn = min(mn, dfs(a, b, pos+1, dp) + 1);
                swap(a[pos], a[i]);
            }
        }
        dp[a] = mn;
        return dp[a];
    }
};