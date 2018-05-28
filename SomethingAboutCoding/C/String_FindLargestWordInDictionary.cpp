/*
Google Intervie Question

Giving a dictionary and a string ‘str’, your task is to find the longest string in dictionary of size x which can be formed by deleting some characters of the given ‘str’.

Examples:

Input : dict = {"ale", "apple", "monkey", "plea"}
str = "abpcplea"
Output : plea

Input  : dict = {"pintu", "geeksfor", "geeksgeeks",
" forgeek"}
str = "geeksforgeeks"
Output : geeksgeeks
*/

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <windows.h>
using namespace std;

class Dictionary {
public:
	string findLongestString(vector<string>& dict, string& str) {
		int strLen = str.size();
		int maxSize = 0;
		int index = -1;
		// for every word in dict, check one word in each loop
		for (int i = 0; i < dict.size(); i++) {
			int j = 0;	// oneWord
			int k = 0;	// str
			// traverse current word and str, check if every char in word also exist in str
			while (j < dict[i].size() && k < str.size()) {
				// current char in word in str
				if (str[k] == dict[i][j]) {
					j++;
				}
				k++;	// current char in word NOT in str, 
			}
			// found all letters in dict[i]
			if (j == dict[i].size()) {
				if (j > maxSize) {
					maxSize = j;
					index = i;
				}
			}
		}

		if (index != -1) {
			return dict[index];
		}
		else
			return "NOTFOUND";
	}
};

int main() {
	Dictionary d;
	vector<string> dict = {
		"pintu", "geeksfor", "geeksgeeks",
		" forgeek", "geeksforgeekss"
	};
	string str = "geeksgeeksfor";

	cout << d.findLongestString(dict, str) << endl;

	system("pause");
	return 0;
}