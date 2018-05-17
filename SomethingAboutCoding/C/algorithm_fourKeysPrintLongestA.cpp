/*
This is a famous interview question asked in Google, Paytm and many other company interviews.

Below is the problem statement.

Imagine you have a special keyboard with the following keys:
Key 1:  Prints 'A' on screen
Key 2: (Ctrl-A): Select screen
Key 3: (Ctrl-C): Copy selection to buffer
Key 4: (Ctrl-V): Print buffer on screen appending it
after what has already been printed.

If you can only press the keyboard for N times (with the above four
keys), write a program to produce maximum numbers of A's. That is to
say, the input parameter is N (No. of keys that you can press), the
output is M (No. of As that you can produce).
Examples:

Input:  N = 3
Output: 3
We can at most get 3 A's on screen by pressing
following key sequence.
A, A, A

Input:  N = 7
Output: 9
We can at most get 9 A's on screen by pressing
following key sequence.
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V

Input:  N = 11
Output: 27
We can at most get 27 A's on screen by pressing
following key sequence.
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V, Ctrl A,
Ctrl C, Ctrl V, Ctrl V
*/
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
	/*
	1. for N <= 6, output is 6
	2. if we tyle Ctrl A, Ctrl C, and the 2 keys follwoing must be Ctrl V x2
	*/
	int findOptimal(int n) {
		if (n <= 6)	return n;

		int max = 0;
		int point;

		// after this point, we only press Ctrl V
		for (point = n - 3; point >= 1; point--) {
			// after point, we only press Ctrl V, so the optimal is (n-point-1) * screen[point-1]
			//	n-point-1 = # of Ctrl V pressed, screen[point-1]=how many As at point
			int curr = (n - point - 1) * findOptimal(point);
			if (curr > max) {
				max = curr;
				cout << "point: " << point << endl;
			}
		}
		return max;
	}
};


/*
和上面的问题相似，不过要简单一些
Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.

Example 1:
Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
Note:
The n will be in the range [1, 1000
*/
class Solution2 {
public:
	/*
	This problem comes down to finding the PRIME FACTORS of n, the explanations is below

	Intuition

	We can break our moves into groups of (copy, paste, ..., paste). Let C denote copying and P denote pasting. Then for example, in the sequence of moves CPPCPPPPCP, the groups would be [CPP][CPPPP][CP].

	Say these groups have lengths g_1, g_2, .... After parsing the first group, there are g_1 'A's. After parsing the second group, there are g_1 * g_2 'A's, and so on. At the end, there are g_1 * g_2 * ... * g_n 'A's.

	We want exactly N = g_1 * g_2 * ... * g_n. If any of the g_i are composite, say g_i = p * q, then we can split this group into two groups (the first of which has one copy followed by p-1 pastes, while the second group having one copy and q-1 pastes).

	Such a split never uses more moves: we use p+q moves when splitting, and pq moves previously. As p+q <= pq is equivalent to 1 <= (p-1)(q-1), which is true as long as p >= 2 and q >= 2.

	Algorithm By the above argument, we can suppose g_1, g_2, ... is the prime factorization of N, and the answer is therefore the sum of these prime factors.
	*/
	int minSteps(int n) {
		if (n == 1)	return 0;

		int ret = 0;
		while (n > 1) {
			int d = 2;
			// from n, extract all 2 factors, 3 factors, ...
			//	when d = 2, repeat the while loop until n has no 2 factors
			while (n%d == 0) {
				ret += d;
				n /= d;
			}
			d++;
		}
		return ret;
	}
};

int main() {
	Solution s;

	cout << s.findOptimal(8);

	return 0;

}