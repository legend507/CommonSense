/*
Given an array arr[], find the maximum j – i such that arr[j] > arr[i]

Examples:

Input: {34, 8, 10, 3, 2, 80, 30, 33, 1}
Output: 6  (j = 7, i = 1)

Input: {9, 2, 3, 4, 5, 6, 7, 8, 18, 0}
Output: 8 ( j = 8, i = 0)

Input:  {1, 2, 3, 4, 5, 6}
Output: 5  (j = 5, i = 0)

Input:  {6, 5, 4, 3, 2, 1}
Output: -1
*/
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Solution {
public:
	// brute force method, O(n^2)
	int findIJ_1(vector<int>& input) {
		int size = input.size();

		int ret = INT_MIN;
		for (int j = size - 1; j > 0; j--) {
			for (int i = j - 1; i >= 0; i--) {
				if (input[j] > input[i])	ret = max(ret, j - i);
			}
		}

		return (ret == INT_MIN ? -1 : ret);
	}

	// O(n)
	//	从左到右找min，从右到左找max 的方法有参考价值
	int findIJ_2(vector<int>& input) {
		int size = input.size();

		// to record min value on current idx, min on left
		vector<int> minFromLeft(size, 0);
		minFromLeft[0] = input[0];
		for (int i = 1; i < size; i++)	minFromLeft[i] = min(input[i], minFromLeft[i - 1]);

		// to record max value on current idx, max on right
		vector<int> maxFromRight(size, 0);
		maxFromRight[size - 1] = input[size - 1];
		for (int i = size - 2; i >= 0; i--) maxFromRight[i] = max(input[i], maxFromRight[i + 1]);

		// 这点需要用实际例子想想
		//	the while loop can find 
		int i = 0, j = 0, ret = INT_MIN;
		while (i < size && j < size) {
			if (minFromLeft[i] < maxFromRight[j]) {
				ret = max(j - i, ret);
				j++;
			}
			else { i++; }
		}
		return (ret == INT_MIN ? -1 : ret);
	}
};



int main() {
	Solution s;
	vector<int> input = { 9, 2, 3, 4, 5, 6, 7, 8, 18, 0 };

	cout << s.findIJ_2(input) << endl;

	return 0;

}