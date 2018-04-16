/*
Largest Sum Contiguous Subarray
找到一个array的subarray，
这个subarray的sum是所有subarray中最大的

以下是Kadane's algorithm，

P.S., 换个角度想，如果input array是 某公司股票的每天变化值，
	则return就是买的timing和卖的timing

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
	Time: O(n)
	返回的是subarray的开始以及结束的index
	*/
	pair<int, int> findMaxSlice(vector<int>& nums) {
		// first=i, second=j, so that nums[i]~nums[j] is a subarray that has max sum
		int len = 0;		// a len tracker, to record len of current subarray
		int lenFinal = 0;	// final length of the subarray
		int end = 0;		// end-lenFinal ~ end, is the subarray

		int size = nums.size();

		int maxSoFar = 0;	//
		int maxHere = 0;	// 记录到现在为止最大的max
		for (int i = 0; i < size; i++) {
			maxSoFar += nums[i];

			// 
			if (maxSoFar > 0) {
				len++;
				if (maxSoFar > maxHere) {
					maxHere = maxSoFar;
					end = i;		// update end boundary of subarray
					lenFinal = len;	// update length of subarray
				}
			}
			// maxSoFar < 0, meaning a new start
			else {
				maxSoFar = 0;
				len = 0;			// reset length to 0
			}
		}

		return make_pair(end - lenFinal + 1, end);
	}
};

int main()
{


	vector<int> nums = { -1000, 1, 2, 4, -1000, 5, 2, 1 };

	Solution s;

	pair<int, int> ret = s.findMaxSlice(nums);



	system("pause");
	return 0;
}

