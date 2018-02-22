/*
This program recursively generate all permutations of an input string,
e.g., if input = abc, then the output is
        abc
        acb
        bac
        bca
        cab
        cba
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
            // if ith char in str is used
            if(usedIndex[i])
                continue;

            oneResult += str[i];
            usedIndex[i] = 1;
            recursePermute(
                oneResult,
                result,
                usedIndex,
                str
            );
            usedIndex[i]=0;
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
