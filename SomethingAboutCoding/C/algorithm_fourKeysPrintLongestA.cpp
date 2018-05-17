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

int main() {
	Solution s;

	cout << s.findOptimal(8);

	return 0;

}