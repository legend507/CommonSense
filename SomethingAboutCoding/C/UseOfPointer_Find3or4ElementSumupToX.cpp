/*
Given an array of distinct elements. The task is to find triplets in array whose sum is zero.

Examples:

Input : arr[] = {0, -1, 2, -3, 1}
Output : 0 -1 1
2 -3 1

Input : arr[] = {1, -2, 1, 0, 5}
Output : 1 -2  1

下面有两个func，一个找3个element加起来等于0
第二个找4个element加起来等于x
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

// a structure of TreeNode
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	// constructor
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	/*
	下面的是找3个，加和是0的元素
	O(n^2)
	*/
	void findZeroSumTriple(vector<int>& input) {
		int len = (int)input.size();

		// 先排序
		sort(input.begin(), input.end());
		for (int i1 = 0; i1<len - 2; i1++) {
			int i2 = i1 + 1;      //
			int i3 = len - 1;

			while (i2 < i3) {
				int result = input[i1] + input[i2] + input[i3];
				if (result == 0) {
					cout << input[i1] << "+" << input[i2] << "+" << input[i3] << "== 0" << endl;
					break;
				}
				else if (result > 0)  i3--;
				else    i2++;
			}
		}
	}

	/*
	下面的是找4个，加和是X的元素
	O(n^3)
	*/
	void findXSumFourEle(vector<int>& input, int x) {
		int len = input.size();

		sort(input.begin(), input.end());

		for (int i1 = 0; i1 < len - 3; i1++) {
			for (int i2 = i1 + 1; i2 < len - 2; i2++) {
				// just like func above, fix 1st and 2nd num, trying to find 3rd and 4th 

				int i3 = i2 + 1;
				int i4 = len - 1;

				while (i3 < i4) {
					int sum = input[i1] + input[i2] + input[i3] + input[i4];

					if (sum == x) {
						cout
							<< input[i1] << "+"
							<< input[i2] << "+"
							<< input[i3] << "+"
							<< input[i4] << "=" << x << endl;
						i3++;
						i4--;
					}
					else if (sum < x)	i3++;
					else i4--;
				}
			}
		}
	}
};

int main(int argc, const char * argv[]) {
	// insert code here...
	Solution sol;
	vector<int> input = { 0, -1, 2, -3, 1 };
	sol.findZeroSumTriple(input);

	vector<int> input2 = { 1, 4, 45, 6, 10, 12 };
	sol.findXSumFourEle(input2, 21);

	system("pause");
	return 0;
}
