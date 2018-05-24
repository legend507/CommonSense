/*
算法上应该没啥问题了，明天应该再认真看一下逻辑
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	/**/
	int partition(vector<int>& nums, int l, int r) {
		int pivot = nums[r];
		int nextPos = l - 1;
		for (int i = l; i < r; i++) {
			if (nums[i] <= pivot) {
				nextPos++;
				swap(nums[i], nums[nextPos]);
			}
		}
		swap(nums[nextPos + 1], nums[r]);

		return nextPos + 1;	// index of pivot
	}
	int findKthSmallest(vector<int>& nums, int k) {
		// e.g., 4th smallest is nums[3] if nums is sorted
		return findKthSmallest_recurse(nums, 0, nums.size() - 1, k);
	}
	int findKthSmallest_recurse(vector<int>& nums, int l, int r, int k) {
		// k取值从1开始到size, l取值从0开始，r取值到size-1为止
		if (k - 1 < l || k - 1 > r)	return INT_MAX;

		int pos = partition(nums, l, r);
		if (pos + 1 == k)	return nums[pos];
		else if (pos + 1 > k)	return findKthSmallest_recurse(nums, l, pos - 1, k);
		else return findKthSmallest_recurse(nums, pos + 1, r, k);

	}


};

int main()
{
	Solution s;

	vector<int> nums = { 12, 3, 5, 7, 4, 19, 26, 6 };

	cout << s.findKthSmallest(nums, 4);


	system("pause");
	return 0;
}

