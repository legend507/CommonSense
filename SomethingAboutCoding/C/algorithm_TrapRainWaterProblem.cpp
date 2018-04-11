/*
If a number is multiple of 3
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
	/*
	|
	|		 |
	|  |	 |
	|__|__|__|
	^		 ^
	l		 r, surface = bars[l]		<- first loop,

	on second loop, fix r, l++, no need to update surface (because highest(r) > surface > now(l))


	*/
	int rainWaterTapped(vector<int>& bars) {
		int l = 0;					// left ptr
		int r = bars.size() - 1;	// right ptr
		int surface = 0;

		int waterAmount = 0;

		/*
		Start from both side,
		Keep the highest bar FIX
		move the lower bar */
		while (l < r) {
			// update surface, only when surface is lower than both l and r
			if (surface < min(bars[l], bars[r]))	surface = min(bars[l], bars[r]);
			// no need to update surface, calc water about this bar
			else waterAmount += surface - min(bars[l], bars[r]);

			// move which side? move lower side!
			bars[l] > bars[r] ? r-- : l++;
		}

		return waterAmount;
	}
};

int main()
{
	vector<int> arr = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
	Solution s;

	cout << s.rainWaterTapped(arr);


	system("pause");
	return 0;
}

