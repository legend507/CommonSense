/*
Largest Sum Contiguous Subarray
找到一个array的subarray，
这个subarray的sum是所有subarray中最大的

以下是Kadane's algorithm，

Kadane是用来找有max value的subarray的，
注意：如果想找min value的话，
1. 把原array所有的element的符号反转(+变-，-变+)
2. 对新的array用Kadane
3. 结果就是原array的min value的subarray


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

	注意，此函数对全部都是negative number的array没用！！！
	*/
	pair<int, int> findMaxSlice(vector<int>& nums) {
		// first=i, second=j, so that nums[i]~nums[j] is a subarray that has max sum
		int len = 0;		// a len tracker, to record len of current subarray
		int lenFinal = 0;	// final length of the subarray
		int end = 0;		// end-lenFinal ~ end, is the subarray

		int size = nums.size();

		int maxSoFar = 0;	// 当前subarray的max, local MAX
		int maxHere = 0;	// 记录到现在为止最大的max, global MAX
		for (int i = 0; i < size; i++) {
			maxSoFar += nums[i];

			// 
			if (maxSoFar > 0) {
				len++;
				// when traverse to -6, program does not go into the following if
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

	/*
	下面的是改进版，对全是negative的array也有效;对正负交错的也有效
	当array中全是negative的时候，找到的是最大的那个负数element
	*/
	pair<int, int> findMaxSlice_AllMighty(vector<int>& nums) {
		int size = nums.size();

		int len = 1;
		int end = 0;
		int lenFinal = 1;

		int maxSoFar = nums[0];	// local max
		int maxHere = nums[0];	// global max

		for (int i = 1; i < size; i++) {
			/* // 如果不用知道subarray的index，用下面就好
			maxSoFar = max(maxSoFar + nums[i], nums[i]);
			maxHere = max(maxSoFar, maxHere);
			*/
			// 为了知道subarray的index，用下面
			if (maxSoFar + nums[i] > nums[i]) {
				// when maxSoFar + nums[i] > nums[i], this means maxSoFar must be > 0!
				len++;
				maxSoFar += nums[i];
			}
			else {
				// if maxSoFar < 0, start from current nums[i]
				maxSoFar = nums[i];	// reset maxSoFar, 和上面的func不同，这里reset成为当前的num[i]
				len = 1;
			}

			if (maxSoFar > maxHere) {
				maxHere = maxSoFar;
				lenFinal = len;	// only modify lenFinal and end in this if
				end = i;		//
			}
		}
		//这个pair是max value subarray的 start和end index
		return make_pair(end - lenFinal + 1, end);
	}

};

int main()
{


	vector<int> nums = { -1000, -1, 1, 2, 4, -6, 5, 2, 1 };
	vector<int> nums_reverse = { 1000, 1, -1, -2, -4, 6, -5, -2, -1 };

	vector<int> negative = { -1000, -1, -2, -4, -6, -5, -2, -10 };

	Solution s;

	// 注意，这两个max value subarray和min value subarray可能会overlap
	pair<int, int> ret_max = s.findMaxSlice_AllMighty(nums);				// nums的max value的subarray
	pair<int, int> ret_min = s.findMaxSlice_AllMighty(nums_reverse);		// nums的min value的subarray



	system("pause");
	return 0;
}

