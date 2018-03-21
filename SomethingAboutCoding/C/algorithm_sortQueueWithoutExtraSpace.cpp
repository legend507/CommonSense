/*
Sorting a queue
without using any extra space

下面的func
时间O(n^2)
空间O(1)
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

class QueueSort {
public:

	/*
	Find min element in 0~boundary,
	return index
	*/
	int findMin(queue<int>& q, int boundary) {
		int size = q.size();
		int temp = INT_MAX;
		int ret;
		for (int i = 0; i < size; i++) {
			// get head element in queue
			int curEle = q.front();
			q.pop();

			// compare head element with temp, if in boundary
			if (i < boundary && temp > curEle) {
				temp = curEle;
				ret = i;
			}

			// push element back to queue
			q.push(curEle);
		}
		return ret;
	}
	/*
	move target element to end of queue,
	while maintaining the sequence of the rest elements
	*/
	void moveEleToEnd(queue<int>& q, int index) {
		int size = q.size();
		int ele;
		for (int i = 0; i < size; i++) {
			int curEle = q.front();
			q.pop();
			if (i == index) {
				ele = curEle;
				continue;		// continue without push
			}
			q.push(curEle);
		}
		q.push(ele);
	}
	int sortAscending(queue<int>& q) {
		int size = q.size();
		for (int i = 0; i < size; i++) {
			// 1st, fidn element
			int index = findMin(q, size - i);
			moveEleToEnd(q, index);
		}

		return 0;
	}
};

int main(int argc, const char * argv[]) {
	queue<int> q;
	q.push(30);
	q.push(11);
	q.push(15);
	q.push(4);

	QueueSort qs;
	qs.sortAscending(q);

	while (q.empty() == false)
	{
		cout << q.front() << " ";
		q.pop();
	}

	system("pause");
	return 0;
}
