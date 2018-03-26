#include    <iostream>
#include    <queue>
#include	<functional>
#include	<stack>
#include	<string>
#include	<iostream>
#include	<unordered_set>
using namespace std;

class Utilities {
public:
	/*
	a O(log y) func to calc x^y	*/
	int power(int x, unsigned int y) {
		int ret = 1;
		while (y > 0) {
			// if last bit of y is 1
			if (y & 0x01) {
				ret = ret * x;
			}
			x = x * x;	// with every loop, x -> x^2
			y = y >> 1;	// with every loop, y -> y/2
		}
		return ret;
	}

	/*
	a O(log min(a,b)) recursive func to find GCD of 2 int,
	e.g., 36 and 60's GCD is 12*/
	int greatestCommonDivisor(int a, int b) {
		// base case
		if (a == 0)	return b;

		// recurse case
		return greatestCommonDivisor(b%a, a);
	}
};

int main() {
	Utilities u;

	cout << u.greatestCommonDivisor(60, -36);

	system("pause");
	return 0;
}
