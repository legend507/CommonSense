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

	/*to decide if a num is odd or even.*/
	string isOddOrEven(int num) {
		if(num&1)   return "odd";
		else        return "even";
	}

	/*How to quickly compute 2^x
	快速计算2^x*/
	int calc2PowX(int x) {
		return (1<<x);
	}
	/*快速check num是否是2的power*/
	bool isPowerOf2(int num) {
		/*
		Explanation: if a num is power of 2, it must have 1 followed by 0s, e.g., 0b100000...
		*/
		return (0 == (num&(num-1)));
	}

};

int main() {
	Utilities u;

	cout << u.greatestCommonDivisor(60, -36);

	system("pause");
	return 0;
}
