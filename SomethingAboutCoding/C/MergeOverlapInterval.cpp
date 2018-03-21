/*
 Given a set of time intervals in any order,
 merge all overlapping intervals into one and output the result which should have only mutually exclusive intervals. Let the intervals be represented as pairs of integers for simplicity.
 
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
        sort(input.begin(), input.end(), interval<int>::compare);
        stack<interval<int>> s;
        // push 1st element to stack
        s.push(input[0]);
        
        for(int i = 1; i < len; i++) {
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
