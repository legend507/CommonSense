/*
Print all Jumping Numbers smaller than or equal to a given value
A number is called as a Jumping Number if all adjacent digits in it differ by 1. The difference between ‘9’ and ‘0’ is not considered as 1.
All single digit numbers are considered as Jumping Numbers. For example 7, 8987 and 4343456 are Jumping numbers but 796 and 89098 are not.

Given a positive number x, print all Jumping Numbers smaller than or equal to x. The numbers can be printed in any order.

Example:

Input: x = 20
Output:  0 1 2 3 4 5 6 7 8 9 10 12

Input: x = 105
Output:  0 1 2 3 4 5 6 7 8 9 10 12
21 23 32 34 43 45 54 56 65
67 76 78 87 89 98 101

Note: Order of output doesn't matter,
i,e., numbers can be printed in any order

JumpingNum就是，各位十位百位。。。的digit大小必须是1
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
	void printJumpingNumsUtil(int x, int start) {
		queue<int> q;
		q.push(start);

		while (!q.empty()) {
			int num = q.front();
			q.pop();

			if (num <= x) {
				cout << num << " ";

				/*
				Example, if num = 19, then lastDigit = 9, so 198 is pushed into queue
				*/
				int lastDigit = num % 10;
				// lastDigit == 0
				if (lastDigit == 0)	q.push((num * 10) + (lastDigit + 1));
				// lastDigit == 9
				else if (lastDigit == 9) q.push((num * 10) + (lastDigit - 1));
				// lastDigit = 1~8
				else {
					q.push((num * 10) + (lastDigit + 1));
					q.push((num * 10) + (lastDigit - 1));
				}
			}
		}
	}

	void printJumpingNum(int x) {
		for (int i = 1; i < 9 && i <= x; i++)	printJumpingNumsUtil(x, i);
	}

};

int main()
{


	vector<int> nums = { 1, 4, 20, 3, 10, 5 };

	Solution s;

	s.printJumpingNum(105);



	system("pause");
	return 0;
}

