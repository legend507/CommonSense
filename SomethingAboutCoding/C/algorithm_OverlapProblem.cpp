/*
 Given a set of time intervals in any order,
 merge all overlapping intervals into one and output the result which should have only mutually exclusive intervals. 
 Let the intervals be represented as pairs of integers for simplicity.
 
 For example, let the given set of intervals be {{1,3}, {2,4}, {5,7}, {6,8} }.
 The intervals {1,3} and {2,4} overlap with each other, so they should be merged and become {1, 4}.
 Similarly {5, 7} and {6, 8} should be merged and become {5, 8}
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

template <typename T>
struct interval {
    T start;
    T end;
    // constructor
    interval(int x, int y) : start(x), end(y) {};
    // operator overload
    friend ostream& operator << (ostream& stream, const interval<T>& obj) {
        stream << "{" << obj.start << "," << obj.end << "}";
        return stream;
    };
    // compare func
    static bool compare(interval<T>& i1, interval<T>& i2) {
        return (i1.start < i2.start);
    }
};

class MergeOverlapping {
public:
    /*
     Method 1, O(n^2)
     Easy Solution
     比较每个interval pair，看有没有overlap
     如果有，则merge 这个pair进入比较靠前的那个interval，消除靠后的那个interval
     */
    vector<interval<int>> method1(vector<interval<int>>& input) {
        vector<interval<int>> ret = input;    // copy input
        int len = (int)ret.size();
        
        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                interval<int> ith = ret[i];
                interval<int> jth = ret[j];
                // check for overlap, 找出不可能Overlap的case，然后！一下
                if ( !(ith.end < jth.start || ith.start > jth.end) ) {
                    // merge interval into new one
                    ret[i].start = min(ith.start, jth.start);
                    ret[i].end = max(ith.end, jth.end);
                    
                    // modify ret vector, delte jth element
                    ret.erase(ret.begin() + j);
                    len--;
                    j--;
                }
            }
        }
        return ret;
    }
    
    /*
     Method 2, O(nlogn)
     先sort，
     然后用stack，loop input中每个元素，
        确保stack top的元素和这些元素不overlap
        如果overlap则pop之后，从新构造元素，然后push回stack
     */
    vector<interval<int>> method2(vector<interval<int>>& input) {
        int len = (int)input.size();
        // 1st, sort the input based on start
        sort(input.begin(), input.end(), interval<int>::compare);   // O(nlogn)

        stack<interval<int>> s;
        // push 1st element to stack
        s.push(input[0]);
        
        for(int i = 1; i < len; i++) {   // O(n)
            interval<int> top = s.top();
            
            // if currnet element in input not overlap with top
            if(top.end < input[i].start)
                s.push(input[i]);
            // overlap found, but do we need to update the end boundary?
            else if(top.end < input[i].end) {
                top.end = input[i].end;
                s.pop();
                s.push(top);
            }
        }
        
        // construct return, this is not necessary
        vector<interval<int>> ret;
        while(!s.empty()) {
            ret.push_back(s.top());
            s.pop();
        }
        return ret;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<interval<int>> input = { { 1,3 },{ 2,4 },{ 5,7 },{ 6,8 } };
    
    MergeOverlapping mo;
    vector<interval<int>> result = mo.method2(input);
    
    for (auto oneEle : result) {
        cout << oneEle << ",";
    }
    
    system("pause");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
/*
Find the point where maximum intervals overlap
Consider a big party where a log register for guest’s entry and exit times is maintained. Find the time at which there are maximum guests in the party. Note that entries in register are not in any order.

Example :

Input: arrl[] = {1, 2, 9, 5, 5}
exit[] = {4, 5, 12, 9, 12}
First guest in array arrives at 1 and leaves at 4,
second guest arrives at 2 and leaves at 5, and so on.

Output: 5
There are maximum 3 guests at time 5.
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

/*
An Efficient Solution is to use sorting n O(nLogn) time. The idea is to consider all events (all arrivals and exits) in sorted order. Once we have all events in sorted order, we can trace the number of guests at any time keeping track of guests that have arrived, but not exited.
arr[]  = {1, 2, 10, 5, 5}
dep[]  = {4, 5, 12, 9, 12}

Below are all events sorted by time.  Note that in sorting, if two
events have same time, then arrival is preferred over exit.
Time     Event Type         Total Number of Guests Present
------------------------------------------------------------
1        Arrival                  1
2        Arrival                  2
4        Exit                     1
5        Arrival                  2
5        Arrival                  3    // Max Guests
5        Exit                     2
9        Exit                     1
10       Arrival                  2
12       Exit                     1
12       Exit                     0

*/
class Solution {
public:
	int findMaxGuests(vector<int>& in, vector<int>& out) {
		// 还是先排序，不关心某个具体的人道in或out时间，只关注在某个时间点 club里有多少人
		sort(in.begin(), in.end());
		sort(out.begin(), out.end());

		int allGuest = 1, ret = 1, time = in[0];
		int inPtr = 1, outPtr = 0;

		while (inPtr < in.size() && outPtr < out.size()) {
			// think about why <= instead of <
			if (in[inPtr] <= out[outPtr]) {
				allGuest++;

				if (allGuest > ret) {
					ret = allGuest;
					time = in[inPtr];
				}
				inPtr++;
			} 
			else {
				allGuest--;
				outPtr++;
			}
		}

		return ret;
	}

};


int main() {
	Solution s;
	vector<int> nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };




	system("pause");
	return 0;

}
