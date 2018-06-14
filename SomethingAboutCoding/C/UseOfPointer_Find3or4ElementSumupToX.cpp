/*
Given an array of distinct elements. The task is to find triplets in array whose sum is zero.

Examples:

Input : arr[] = {0, -1, 2, -3, 1}
Output : 0 -1 1
2 -3 1

Input : arr[] = {1, -2, 1, 0, 5}
Output : 1 -2  1

下面有两个func，一个找3个element加起来等于0
第二个找4个element加起来等于x

还有，如果要找2个element加起来等于某个特定值的话，也可以先sort array；
或者用unordered_set，遍历input素有元素，计算[特定值-当前element]，看结果在不在unordered_set里面，不在的话把当前element放进unordered_set
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <algorithm>
using namespace std;

class Solution {
public:
	/*
	下面的是找3个，加和是0的元素
	O(n^2)
	*/
	void findZeroSumTriple(vector<int>& input) {
		int len = (int)input.size();

		// 先排序
		sort(input.begin(), input.end());

		// i1 traverses from 0~n-3
		for (int i1 = 0; i1<len - 2; i1++) {
			// when i1 increases, fix i1
			int i2 = i1 + 1;      	// i2 start to change from i1+1
			int i3 = len - 1;		// i3 start to change from n-1
			
			// this while loop, fix i1, increase i2/decrease i3
			while (i2 < i3) {
				int result = input[i1] + input[i2] + input[i3];
				if (result == 0) {
					cout << input[i1] << "+" << input[i2] << "+" << input[i3] << "== 0" << endl;
					break;
				}
				// since sorted, if result now is too big, decrease so that input[i3] becomes smaller
				else if (result > 0)  i3--;
				// result now is too small, increase i2 so that input[i2] becomes bigger
				else    i2++;
			}
		}
	}

	/*
	下面的是找4个，加和是X的元素
	O(n^3)
	*/
	void findXSumFourEle(vector<int>& input, int x) {
		int len = input.size();

		sort(input.begin(), input.end());

		/*
		Same idea, instead this time fix i1 and i2, i3 start from i2+1, i4 start from n-1	*/
		for (int i1 = 0; i1 < len - 3; i1++) {
			for (int i2 = i1 + 1; i2 < len - 2; i2++) {
				// just like func above, fix 1st and 2nd num, trying to find 3rd and 4th 

				int i3 = i2 + 1;
				int i4 = len - 1;

				while (i3 < i4) {
					int sum = input[i1] + input[i2] + input[i3] + input[i4];

					if (sum == x) {
						cout
							<< input[i1] << "+"
							<< input[i2] << "+"
							<< input[i3] << "+"
							<< input[i4] << "=" << x << endl;
						i3++;
						i4--;
						// unlike the func above, no break here, because I want to cout all combines

					}
					else if (sum < x)	i3++;
					else i4--;
				}
			}
		}
	}
	/*there is a Hashing based O(n^2) solution, 
1. Store sums of all pairs in a hash table
2. Traverse through all pairs again and search for X – (current pair sum) in the hash table.
3. If a pair is found with the required sum, then make sure that all elements are distinct array elements and an element is not considered more than once.
// A hashing based  CPP program to find if there are 
// four elements with given sum.
#include <bits/stdc++.h>
using namespace std;
 
// The function finds four elements with given sum X
void findFourElements (int arr[], int n, int X)
{
    // Store sums of all pairs in a hash table
    unordered_map<int, pair<int, int>> mp;
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            mp[arr[i] + arr[j]] = {i, j};
 
    // Traverse through all pairs and search
    // for X - (current pair sum).    
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            int sum = arr[i] + arr[j];
 
            // If X - sum is present in hash table,            
            if (mp.find(X - sum) != mp.end())
            {
 
                // Making sure that all elements are
                // distinct array elements and an element
                // is not considered more than once.
                pair<int, int> p = mp[X - sum];
                if (p.first != i && p.first != j &&
                        p.second != i && p.second != j)
                {
                    cout << arr[i] << ", " << arr[j] << ", "
                         << arr[p.first] << ", "
                         << arr[p.second];
                    return;
                }
            }
        }
    }
}
	
	
	*/
};

int main(int argc, const char * argv[]) {
	// insert code here...
	Solution sol;
	vector<int> input = { 0, -1, 2, -3, 1 };
	sol.findZeroSumTriple(input);

	vector<int> input2 = { 1, 4, 45, 6, 10, 12 };
	sol.findXSumFourEle(input2, 21);

	system("pause");
	return 0;
}
