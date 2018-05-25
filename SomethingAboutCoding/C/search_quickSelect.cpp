/*
K’th Smallest/Largest Element in Unsorted Array | Set 1
Given an array and a number k where k is smaller than size of array, we need to find the k’th smallest element in the given array. It is given that ll array elements are distinct.

Examples:

Input: arr[] = {7, 10, 4, 3, 20, 15}
k = 3
Output: 7

Input: arr[] = {7, 10, 4, 3, 20, 15}
k = 4
Output: 10
*/
/*
K’th Smallest/Largest Element in Unsorted Array | Set 1
Given an array and a number k where k is smaller than size of array, we need to find the k’th smallest element in the given array. It is given that ll array elements are distinct.

Examples:

Input: arr[] = {7, 10, 4, 3, 20, 15}
k = 3
Output: 7

Input: arr[] = {7, 10, 4, 3, 20, 15}
k = 4
Output: 10

注意，如果问题是要求一个array的median的时候，就是 K= size/2	！！！

*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
	/*Method 1, sort the input vector, and return
	O(nlogn)*/
	int findKth_1(vector<int>& nums, int k) {
		// Don't forget input check

		sort(nums.begin(), nums.end());	// O(nlogn)
		return nums[k - 1];
	}
	////////////////////////////////////////////////////////

	/*Method 2, quick select
	这个方法是based on QuickSort的partition func，
	average: O(n) <- why O(n)? Because n + (n/2) + (n/4) + .... = O(n)
	worse: O(n^2)
	To avoid worse from happening for a already sorted array, use partition_random()	*/
	int findKth_2(vector<int>& nums, int k) {
		// e.g., 4th smallest is nums[3] if nums is sorted
		return findKth_2_recurse(nums, 0, nums.size() - 1, k);
	}
	int findKth_2_recurse(vector<int>& nums, int l, int r, int k) {
		// k取值从1开始到size, l取值从0开始，r取值到size-1为止
		if (k - 1 < l || k - 1 > r)	return INT_MAX;

		int pos = partition(nums, l, r);		// pivot's index, 
		if (pos + 1 == k)	return nums[pos];
		else if (pos + 1 > k)	return findKth_2_recurse(nums, l, pos - 1, k);
		else return findKth_2_recurse(nums, pos + 1, r, k);
	}
	/* 解释一下partition的动作
	1. 把arry的最后一个当成pivot
	2. 用nextPos当成指针，遍历l到r的所有元素，如果<=pivot，则交换nums[nextPos] 和 nums[i]，然后nextPos++
	3. 遍历结束后，交换array最后一个元素和nums[nextPos]
	4. 返回pivot的index*/
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
	/*
	since partition always choose nums[r] as pivot,
	this func move nums[r] to a random position in l~r,
	*/
	int partition_Random(vector<int>& nums, int l, int r) {
		int range = r - l + 1;
		int pivot = l + rand() % range;

		swap(nums[pivot], nums[r]);

		return partition(nums, l, r);
	}

};

int main()
{
	vector<int> nums = { 12, 3, 5, 7, 4, 19, 26 };
	Solution s;


	cout << s.findKth_1(nums, 4) << endl;
	cout << s.findKth_2(nums, 4) << endl;

	return 0;
}