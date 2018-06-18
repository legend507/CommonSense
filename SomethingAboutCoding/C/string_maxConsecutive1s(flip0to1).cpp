/*
Google Interview Qs

Max Consecutive Ones II
Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
After flipping, the maximum number of consecutive 1s is 4.
Note:

The input array will only contain 0 and 1.
The length of input array is a positive integer and will not exceed 10,000
Follow up:
What if the input numbers come in one by one as an infinite stream? In other words, you can't store all numbers coming from the stream as it's too large to hold in memory. Could you solve it efficiently?
*/

#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
#include	<unordered_map>
#include	<sstream>			// istringstream and ostringstream
#include	<set>
#include	<climits>
#include	<algorithm>
using namespace std;

///////////////////////////////////////////////////////////////////////
class Solution {
public:
	/*
	下面方法是我原创，不过只beat 15%左右，需要好一些的方法
	*/
	int findMaxConsecutiveOnes(vector<int>& nums) {
		vector<pair<int, int>> zeroIdx;
		int size = nums.size();
		int count1 = 0;
		for(int i = 0; i < size; i++) {
			if (nums[i] == 1)	count1++;
			// nums[i] = 0
			else {
				zeroIdx.push_back({ i, count1 });
				count1 = 0;
			}
		}
		zeroIdx.push_back({ size, count1 });

		int max1s = 0;
		if (zeroIdx.size() == 1) return zeroIdx[0].second;

		for (int i = 0; i < zeroIdx.size()-1; i++) {
			pair<int, int> cur = zeroIdx[i];
			pair<int, int> nxt = zeroIdx[i + 1];

			// found one 0 to flip
			if (cur.first + 1 == nxt.first-nxt.second) {
				max1s = max(max1s, cur.second + 1 + nxt.second);
			}
			// separate by more than one 0s
			else {
				max1s = max(max1s, max(cur.second, nxt.second));
			}
		}
		return max1s;
	}
/////////////////////////////////////////////////////////
	/*下面方法是别人的，beat 46%，想法也比我的简单*/
	int findMaxConsecutiveOnes(vector<int>& nums) {
		auto count{ 0 };
		auto preCount{ 0 };
		auto res{ 0 };

		for (auto num : nums) {
			if (num == 0) {
				preCount = count + 1;	// num = 0, but we can flip it, hence +1
				count = 0;
			}
			else {
				count++;
			}
			res = max(res, count + preCount);
		}
		return res;
	}

};

int main() {
	Solution s;
	vector<int> nums = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1};
	s.findMaxConsecutiveOnes(nums);

	system("pause");
	return 0;
}