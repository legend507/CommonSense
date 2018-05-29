/*
This program recursively generate all permutations of an input string,
e.g., if input = abc, then the output is
        abc
        acb
        bac
        bca
        cab
        cba
O(n*n!)
*/


#include    <string>
#include    <iostream>
#include    <vector>
using namespace std;

class Solution {
public:
    vector<string> stringPermutation(string str) {
        vector<string> result;
        string oneResult;

        // visited or not 
        vector<int> usedIndex (str.size(), 0);

        recursePermute(
            oneResult,
            result, 
            usedIndex,
            str);

        return result;
    }
private:
    void recursePermute(
        string oneResult,
        vector<string> & result, 
        vector<int> & usedIndex,
        string & str) {
        
        // base case
        if(oneResult.size() == str.size()) {
            result.push_back(oneResult);
            return;
        }

        // recurse case
        for(int i = 0; i < str.size(); i++) {
            // if ith char in str is used, skip
            if(usedIndex[i])
                continue;

            // if ith char not used, add to oneResult, mark as used     
            oneResult += str[i];
            usedIndex[i] = 1;   // mark as used
            recursePermute(
                oneResult,
                result,
                usedIndex,
                str
            );
            usedIndex[i]=0;     // unmark
            oneResult = oneResult.substr(0, oneResult.size()-1);
        }
    }

};

int main() {
    string str = "abc";

    Solution sol;

    vector<string> result = sol.stringPermutation(str);

    for(auto oneStr : result) {
        cout << oneStr << endl;
    }
    return 0;
}
