/*
Google Interview Qs 这个问题觉得有些不太好，记一下hashMap的count()的用法，不用太注重理解

You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
For number 1 in the first array, the next greater number for it in the second array is 3.
For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
For number 2 in the first array, the next greater number for it in the second array is 3.
For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
Note:
All elements in nums1 and nums2 are unique.
The length of both nums1 and nums2 would not exceed 1000.
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
	vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
		stack<int> s;
		unordered_map<int, int> m;

		// traverse nums, say nums={1,3,4,2}
		//	after for loop, m[1]=3, m[3]=4, 
		for (auto n : nums) {
			while (s.size() && s.top() < n) {
				m[s.top()] = n;
				s.pop();
			}
			s.push(n);
		}

		vector<int> ret;
		// m.count(n) 查找key=n的元素，如果存在，则返回1 (因为是hashMap，所以count的返回值只可能是0或1)
		for (auto n : findNums) ret.push_back(m.count(n) ? m[n] : -1);
	}
};

int main() {
	Solution s;
	vector<vector<int>> nums = { {1, 2, 3},{4, 5, 6},{7, 8, 9} };


	system("pause");
	return 0;

}
