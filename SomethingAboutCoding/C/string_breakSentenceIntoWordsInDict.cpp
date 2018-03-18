/*
 Given an input string and a dictionary of words, find out if the input string can be segmented into a space-separated sequence of dictionary words. See following examples for more details.
 This is a famous Google interview question, also being asked by many other companies now a days.
 
 Consider the following dictionary
 { i, like, sam, sung, samsung, mobile, ice,
 cream, icecream, man, go, mango}
 
 Input:  ilike
 Output: Yes
 The string can be segmented as "i like".
 
 Input:  ilikesamsung
 Output: Yes
 The string can be segmented as "i like samsung"
 or "i like sam sung".
 */

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <stack>
using namespace std;

class DictionarySearch {
public:
    // check if word is in dict
    bool isWordInDict(string word, vector<string>& dict) {
        int dictSize = (int)dict.size();
        
        for(int i = 0; i < dictSize; i++) {
            if(word.compare(dict[i]) == 0)
                return true;
        }
        return false;
    }
    
    /*
     Method1
     递归，找到一个解法之后就返回
     有一点需要改进，怎样找到所有可能的words组合？
     */
    bool breakSentence1(string sentence, vector<string>& dict) {
        int len = (int)sentence.size();
        
        // base case
        if(len == 0)    return true;
        
        // recurse case
        for(int i = 1; i <= len; i++) {
            if(isWordInDict(sentence.substr(0, i), dict)
               && breakSentence1(sentence.substr(i, len-i), dict)) {
                cout <<sentence.substr(0, i) << " ";
                // 如果在下面返回，则只找一个组合
                return true;
            }
        }
        return false;
    }
    /*
     Method2
     DP，
     从sentence 0 到 len-1依次检查，
     如果dp[i] = true, 意思就是sentence[0~i-1]可以从dict中构成
        则从i看往后的char，如果sentence[i~j]在dict中，则dp[j]=true
     最后看dp[len]
     */
    bool breakSentence2(string sentence, vector<string>& dict) {
        int len = (int)sentence.size();
        
        // dp[i] = if sentence[0 ~ i-1] can be break into words
        vector<bool> dp(len+1, false);
        /*
         case 1: dp[0] = false, for an empty sentence ca not be break into words,
         case 2: i > 0,
            dp[i] = true, if sentence[0 ~ i-1] is a word in dict,
         */
        
        for(int i = 1; i <= len; i++) {
            // check if sentence[0~i-1] is a complete word in dict
            if(dp[i] == false && isWordInDict(sentence.substr(0,1), dict))
                dp[i] = true;
            
            
            // if sentence[0 ~ i-1] is in dict, check the chars behind it, if [i~(end)] is also in dict
            if(dp[i] == true) {
                if(i == len)
                    return true;        // if i is the end of sentence, meaning sentence can be constructed from words in dict
                
                for(int j = i+1; j <= len; j++) {
                    // same as above, we already know sentence[0~i-1] is TRUE, based on that check sentence[i~j]
                    if(dp[j] == false && isWordInDict(sentence.substr(i,j-i), dict))
                        dp[j] = true;
                }
            }
        }
        return dp[len];
    }
    
    /*
     Method3, BackTracing
     注意，这个方法可以print所有可能组合
     */
    void breakSentence3(string sentence, vector<string>& dict) {
        doRecurse(sentence, (int)sentence.size(), "", dict);
    }
    void doRecurse(string str, int len, string result, vector<string>& dict) {
        for(int i = 1; i <= len; i++ ) {
            string headStr = str.substr(0, i);
            
            // if sentence[0~i-1] is in dict,
            //  check if we reached the sentence end, if YES, print result
            //  if NO, recurse from sentence[i]
            if(isWordInDict(headStr, dict)) {
                if(i == len) {
                    result += headStr;
                    cout << result << endl;
                    return;
                }
                
                // use sentence[i~end] as input, and add current headStr to result
                doRecurse(str.substr(i, len-i), len-i, result + headStr + " ", dict);
            }
        }
    }
};


int main() {
    vector<string> dict = {"mobile","samsung","sam","sung",
        "man","mango", "icecream","and",
        "go","i","love","ice","cream"};
    string str = "iloveicecreamandmango";
    
    DictionarySearch ds;
    ds.breakSentence3(str, dict);
    
    system("pause");
    return 0;
}

