/*
Determin if input x is a substring of input y, 
e.g., "bat"is a substring of abate, but not "beat"
顺序有关
*/

#include <string>
#include <iostream>
using namespace std;

class Solution {
public: 
    // y is longer string, x is shorter string
    bool isSubstring(string x, string y){
        if(x.size() == 0 && y.size() == 0)  return true;

        // i traverse string y
        for(int i = 0; i < y.size(); i++) {
            bool notMatch = false;
            // j traverse x, compare y[i+j] with x[j], if not same, flag notMatch
            for(int j = 0; j < x.size(); j++) {
                if(y[i+j] != x[j]) {
                    notMatch = true;
                    break;  // stop traverse x
                }
            }
            // after traverse x, if notMatch flag is still false, then found substring at y[i]
            if(notMatch == false)    return true;
        }
        return false;
    }
};


