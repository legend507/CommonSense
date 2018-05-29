/*
Google Interview Question
Given a length n, count the number of strings of length n that can be made using ‘a’, ‘b’ and ‘c’ 
	with at-most one ‘b’ and two ‘c’s allowed.
*/

#include <vector>
#include <iostream>
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

class ConstructString {
private:
	
	vector<string> allResult;

	/*brute force method,
	the input parameter oneResult is pass by value!!!	*/
	int count(int n, int maxB, int maxC, string oneResult) {
		// base case - using too many b and c, terminate recursion
		if (maxB < 0 || maxC < 0)	return 0;
		// used up all n, current length == n, found an answer
		if (n == 0) { 
			allResult.push_back(oneResult); 
			return 1; 
		}
		// used up all b and c, only can use a, no need for recursion
		if (maxB == 0 && maxC == 0) { 
			while (n > 0) {
				oneResult += "a";
				n--;
			}
			allResult.push_back(oneResult);
			return 1; 
		}

		// recurse case, we can choose to use a, b, or c
		int ret = 0;
		ret += count(n - 1, maxB, maxC, oneResult+"a");			// choose to use a
		ret += count(n - 1, maxB - 1, maxC, oneResult+"b");		// choose to use b
		ret += count(n - 1, maxB , maxC - 1, oneResult+"c");	// choose to use c

		return ret;
	}

public:
	/*入口函数*/
	int howMany(int n) {
		int maxB = 1;
		int maxC = 2;
		string oneResult;
		return count(n, maxB, maxC, oneResult);
	}

	void printAllResult() {
		for (auto oneStr : allResult) {
			cout << oneStr << endl;
		}
	}

};

int main() {
	ConstructString cs;

	cout << cs.howMany(4) << endl;
	cs.printAllResult();

	system("pause");
	return 0;
}