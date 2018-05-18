/*
Find subarray with given sum | Set 1 (Nonnegative Numbers)
Given an unsorted array of nonnegative integers, find a continous subarray which adds to a given number.

Examples :

Input: arr[] = {1, 4, 20, 3, 10, 5}, sum = 33
Ouptut: Sum found between indexes 2 and 4

Input: arr[] = {1, 4, 0, 0, 3, 10, 5}, sum = 7
Ouptut: Sum found between indexes 1 and 4

Input: arr[] = {1, 4}, sum = 0
Output: No subarray found
There may be more than one subarrays with sum as the given sum. The following solutions print first such subarray.

Source: Google Interview Question
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
#include <unordered_set>
using namespace std;

class Solution {
public:

	/*
	O(n^2)
	*/
	pair<int, int> findMaxSlice(vector<int>& nums, int target) {
		pair<int, int> ret(-1,-1); // <start, end> of subarray

		// input check
		int size = nums.size();
		// pick a start point i, and check all subarrays from i
		for (int i = 0; i < size; i++) {
			int sum = nums[i];

			// nums[i] ~ nums[j] is the subarray
			for (int j = i + 1; j <= size; j++) {

				// found
				if (sum == target) {
					ret.first = i;
					ret.second = j - 1;
					return ret;
				}

				// all elements NONnegative, or reached end
				if (sum > target || j == size) break;

				sum += nums[i];
			}
		}

		// NOT Found
		return ret;

	}

	pair<int, int> findMaxSlice2(vector<int>& nums, int target) {
		pair<int, int> ret(-1, -1); // <start, end> of subarray
		int size = nums.size();
		int sum = nums[0];
		int subArrayStart = 0;

		/*
		The thinking is, 
		sum one by one, if sum > target, remove from head, 
		it's like finding a window
		*/
		for (int i = 1; i <= size; i++) {
			// process when sum > target
			while (sum > target && subArrayStart < i) {
				sum -= nums[subArrayStart];
				subArrayStart++;
			}

			// when sum == target
			if (sum == target) {
				ret.first = subArrayStart;
				ret.second = i-1;
				return ret;
			}

			// when sum still < target
			sum += nums[i];
		}

		// NOT Found
		return ret;

	}

};

int main()
{


	vector<int> nums = { 1, 4, 20, 3, 10, 5 };

	Solution s;

	s.findMaxSlice2(nums, 33);




	system("pause");
	return 0;
}

