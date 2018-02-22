/*
说明：
    removeMultiCharFromString可以从第一个input string中移除所有在第二个string中存在的char
    例如：input为“fuck you !”，“you ”，返回结果是“fck!”
*/

#include    <string>
#include    <iostream>
using namespace std;

class Solution {
public:

    string  removeMultiCharFromString(string str, string removeChar) {
        int charTable[256] = {0};       // initialize with 256 0s
        string ret;

        // 用charTable来记录需要移除的char
        for(auto oneChar:removeChar)
            charTable[oneChar] = 1;

        for(auto oneChar:str) {
            // 遍历所有char，如果不在移除table中，则加入ret string
            if( !charTable[oneChar]) {
                ret += oneChar;
            }
        }
        return ret;
    }
};

int main() {
    string str= {"fuck you !"};
    string removeChar = {"you "};

    Solution sol;

    cout << sol.removeMultiCharFromString(str, removeChar) << endl;

    return 0;
}
