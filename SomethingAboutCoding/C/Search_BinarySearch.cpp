/*
下面是BinarySearch的C++实装
有 递归方法
有 非递归方法

O(logn)
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

class BinarySearch {
public:
	/*
	Method 1,
	递归方法*/
	int recursiveMethod(vector<int>& arr, int target) {
		int start = 0;
		int end = arr.size() - 1;

		return doRecurse(arr, target, start, end);
	}
	int doRecurse(vector<int>& arr, int target, int start, int end) {
		if (end < 1)	return -1;		// not found

		int middle = start + (end - start) / 2;
		// base case - found target
		if (arr[middle] == target) {
			return middle;
		}

		// recurse case
		/// 
		if (arr[middle] > target)	return doRecurse(arr, target, start, middle);
		///
		if (arr[middle] < target)	return doRecurse(arr, target, middle, end);
	}

	/*
	Method 2,
	非递归方法*/
	int iterateMethod(vector<int>& arr, int target) {
		int start = 0;
		int end = arr.size() - 1;

		while (start <= end) {
			int middle = start + (end - start) / 2;
			///
			if (arr[middle] == target)	return middle;
			///
			if (arr[middle] > target) end = middle - 1;
			///
			if (arr[middle] < target) start = middle + 1;
		}
		return -1;	// not found
	}
};

int main(int argc, const char * argv[]) {
	vector<int> arr = { 2, 3, 4, 10, 40 };
	BinarySearch bs;
	cout << bs.iterateMethod(arr, 10);

	system("pause");
	return 0;
}
