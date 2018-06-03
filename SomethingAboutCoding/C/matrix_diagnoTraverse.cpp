/*
Google Interview Qs

Given a matrix of M x N elements (M rows, N columns), return all elements of the matrix in diagonal order as shown in the below image.

Example:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output:  [1,2,4,7,5,3,6,8,9]
Explanation: refer to the following URL
https://leetcode.com/explore/interview/card/google/63/sorting-and-searching-4/452/

Note:
The total number of elements of the given matrix will not exceed 10,000.
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
    /*下面方法是我自己的，beat 84%，还不错
    计算出每次的row和col的index*/
	vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
		// supporse nxn matrix, then 2n-1 diagno
		int row = matrix.size();
		if (row == 0) return vector<int>() = {};
		int col = matrix[0].size();

		vector<int> ret;

		// when n = 3, i = 0~5; when n=4, i = 0~7
		for (int i = 0; i < row + col - 1; i++) {
            
            // rowIdx和colIdx是每次loop开始的index，然后delta决定diagno的走向
			int rowIdx, colIdx;
			int rowDelta, colDelta;
			// i is odd, traverse from top to bottom
			if (i & 0x01) { 
				colIdx = (i <= col - 1 ? i : col - 1);
				rowIdx = i - colIdx;
				rowDelta = 1, colDelta = -1; // from top to bottom, so row# decreases, col# increases
			}
			// i is even, traverse from bottome to top
			else { 
				rowIdx = (i <= row - 1 ? i : row - 1);	// index of start point
				colIdx = i - rowIdx;
				rowDelta = -1, colDelta = 1; 
			}

			while (rowIdx >= 0 && rowIdx <= row - 1
				&& colIdx >= 0 && colIdx <= col - 1) {
				ret.push_back(matrix[rowIdx][colIdx]);
				rowIdx += rowDelta;
				colIdx += colDelta;
			}
		}
		return ret;
	}
};

int main() {
	Solution s;
	vector<vector<int>> nums = { {1, 2, 3},{4, 5, 6},{7, 8, 9} };

	s.findDiagonalOrder(nums);

	system("pause");
	return 0;

}
