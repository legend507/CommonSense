/*
 Given a dictionary, a method to do lookup in dictionary and a M x N board where every cell has one character. Find all possible words that can be formed by a sequence of adjacent characters. Note that we can move to any of 8 adjacent characters, but a word should not have multiple instances of same cell.
 
 Example:
 
 Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
 boggle[][]   = {{'G','I','Z'},
                 {'U','E','K'},
                 {'Q','S','E'}};
 isWord(str): returns true if str is present in dictionary
 else false.
 
 Output:  Following words of dictionary are present
 GEEKS
 QUIZ
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

/*
 TrieNode structure
 一个可以有多个分支的Tree结构
 */
struct TrieNode
{
    // there are 26 letters in alphabit, hence 26
    TrieNode *child[26];
    
    // to indicate if current node is a leaf (meaning no child)
    bool isLeaf;
    
    // constructor
    TrieNode() {
        for(int i = 0; i < 26; i++)
            child[i] = NULL;
        isLeaf = false;
    }
};

class DictionarySearch {
public:
    /*
     想法1:对每个cell，用DFS
     用递归的方法，从一个cell开始，到所有cell都走完为止，
     每到一个新cell，将cell里的char加入string，然后再看现在的string是否在searchList中
     */
    void findAllCombi(vector<vector<char>>& dict, vector<string>& searchList) {
        int row = (int)dict.size();
        int col = (int)dict[0].size();
        
        // a matrix same size as dict, to track if visited or not
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        
        string oneStr;  // an empty string
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                findAllCombiFromCell(i, j, dict, searchList, visited, oneStr);
            }
        }
    }
    /*
     Check是否searchList中包含oneStr
     */
    bool isWordInList(vector<string>& searchList, string& oneStr) {
        for(int i = 0; i < searchList.size(); i++)
            if(oneStr.compare(searchList[i]) == 0)
                return true;
        return false;
    }
    /*看当前row和col是否为有效值*/
    bool isRowColValid(int row, int col, vector<vector<char>>& dict) {
        if(row < 0 || col < 0 || row >= dict.size() || col >= dict[0].size())
            return false;
        return true;
    }
    /*
     递归func，
     以input （row，col）为基准，遍历周围8个cell
     如果那个cell以前没有被check过的话，以那个cell为基准recurse
     注意！！，用visited matrix记录走过没有的方法挺好，记住一下
     */
    void findAllCombiFromCell(int i, int j,
                              vector<vector<char>>& dict,
                              vector<string>& searchList,
                              vector<vector<bool>>& visited,
                              string& oneStr ) {
        visited[i][j] = true;   /*用这个matrix当作check，当所有cell都true的时候，停止*/
        oneStr += dict[i][j];
        
        // check if current oneStr is in searchList, if YES, print
        if(isWordInList(searchList, oneStr))
            cout << oneStr << endl;
        
        // goto adjacent 8 cells one by one
        for(int curRow = i-1; curRow <= i+1; curRow++)
            for(int curCol = j-1; curCol <=j+1; curCol++)
                // if current (row, col) valid, and the cell is not visited
                if(isRowColValid(curRow, curCol, dict) && !visited[curRow][curCol])
                    findAllCombiFromCell(curRow, curCol, dict, searchList, visited, oneStr);
        
        // 在试过当前cell的所有相邻的8个cell之后，reset visited matrix，然后返回
        oneStr.erase(oneStr.size() -1);
        visited[i][j] = false;
    }
/*=================================================================================================*/
    
    /*
     想法2:So called Tried solution
     先看searchList，把其中左右的word都建成一个trie（用insertTrie func）
     然后再遍历dict，比较每个cell中的char和trie的root的child[],如果相同的话，就如递归
     */
    void trieMethod(vector<vector<char>>& dict, vector<string>& searchList) {
        TrieNode* root = new TrieNode();
        
        // 将searchList中所有word都加入Trie中
        for(auto oneStr : searchList)
            insertTrie(root, oneStr);
        
        // a visited matrix
        vector<vector<bool>> visited(dict.size(), vector<bool>(dict[0].size(), false));
        string oneStr;
        
        // same as 想法1，从每个cell开始，recurse
        for(int i = 0; i < dict.size(); i++) {
            for(int j = 0; j < dict[0].size(); j++) {
                // if the letter in current cell is an initial letter (meaning child node is not NULL)
                if(root->child[dict[i][j] - 'A']) {
                    oneStr += dict[i][j];
                    searchTrie(root->child[dict[i][j] - 'A'],
                               dict,
                               visited, i, j,
                               oneStr);
                    oneStr = "";
                }
            }
        }
    }
    /*
     return true if row, col in range, and visited[i][j] == false
     */
    bool isRowColValid(int row, int col, vector<vector<char>>& dict, vector<vector<bool>>& visited) {
        if(row < 0 || col < 0 || row >= dict.size() || col >= dict[0].size())
            return false;
        if(visited[row][col] == true)
            return false;
        return true;
    }
    
    /*递归func，
    已经在入口func trieMethod中找到了当前cell中的char和trie中root下第一层的某个child match
    此func在做的事是，检查那个match的child的26个child，并同时看当前cell的相邻8个cell
    直到到达了trie的一个leaf（此时就知道找到了这个word）
    注意！！！用visited matrix标记是个不错的方法，记一下
     */
    void searchTrie(TrieNode* root,
                    vector<vector<char>>& dict,
                    vector<vector<bool>>& visited,
                    int i,
                    int j,
                    string oneStr) {
        // base case - if reach the leaf node of a branch
        if(root->isLeaf)    cout << oneStr << endl;
        
        // recurse case
        //  if current (i,j) is not visited
        if(isRowColValid(i, j, dict, visited)) {
            visited[i][j] = true;
            
            // traverse all child of current root
            for(int k = 0; k < 26; k++) {
                if(root->child[k] != NULL) {
                    // convert current index to char
                    char curChar = (char)k + 'A';
                    
                    // check the adjacent 8 cells
                    //  1. the cell mast be valid and not visited
                    //  2. dict[i][j] must match current char in trie
                    // 右下
                    if(isRowColValid(i+1, j+1, dict, visited)
                       && dict[i+1][j+1] == curChar)    searchTrie(root->child[k], dict, visited, i+1, j+1, oneStr+curChar);
                    // 右
                    if(isRowColValid(i, j+1, dict, visited)
                       && dict[i][j+1] == curChar)      searchTrie(root->child[k], dict, visited, i, j+1, oneStr+curChar);
                    // 右上
                    if(isRowColValid(i-1, j+1, dict, visited)
                       && dict[i-1][j+1] == curChar)      searchTrie(root->child[k], dict, visited, i-1, j+1, oneStr+curChar);
                    // 上
                    if(isRowColValid(i-1, j, dict, visited)
                       && dict[i-1][j] == curChar)      searchTrie(root->child[k], dict, visited, i-1, j, oneStr+curChar);
                    // 左上
                    if(isRowColValid(i-1, j-1, dict, visited)
                       && dict[i-1][j-1] == curChar)      searchTrie(root->child[k], dict, visited, i-1, j-1, oneStr+curChar);
                    // 左
                    if(isRowColValid(i, j-1, dict, visited)
                       && dict[i][j-1] == curChar)      searchTrie(root->child[k], dict, visited, i, j-1, oneStr+curChar);
                    // 左下
                    if(isRowColValid(i+1, j-1, dict, visited)
                       && dict[i+1][j-1] == curChar)      searchTrie(root->child[k], dict, visited, i+1, j-1, oneStr+curChar);
                    // 下
                    if(isRowColValid(i+1, j, dict, visited)
                       && dict[i+1][j] == curChar)      searchTrie(root->child[k], dict, visited, i+1, j, oneStr+curChar);
                }
            }
            // end of all recurse, reset cell to not visited
            visited[i][j] = false;
        }
    }
    /*use this func to construct trie
     e.g., The trie I build for the following test case is 
           After insertion Tre look like (leaf nodes are O, S, R, Z )
                       root
                    /   |    \
                    G   F     Q
                 /  |   |     |
                O   E   O     U
                    |   |     |
                    E    R     I
                    |         |  
                    K         Z 
                    |   
                    S  
     
     */
    void insertTrie(TrieNode* root, string key) {
        int keyLen = (int)key.size();
        TrieNode* pChild = root;
        
        // suppose key = "oneword", the following loop builds a branch by going through o->n->e->w->o->r->d
        for(int i = 0; i < keyLen; i++) {
            int index = key[i] - 'A';   // assume we only have capital letters,
            
            // if key[i] does not already exist, create a new TrieNode
            if(pChild->child[index] == NULL)
                pChild->child[index] = new TrieNode();
            
            // move pChild to lower node
            pChild = pChild->child[index];
        }
        
        // mark the last letter as leaf
        pChild->isLeaf = true;
    }
    
};


int main() {
    
    vector<vector<char>> dict = {{'G','I','Z'},
                                {'U','E','K'},
                                {'Q','S','E'}};
    vector<string> searchList = {"GEEKS", "FOR", "QUIZ", "GO"};
    
    // 1st method (recurse)
    DictionarySearch ds;
    ds.findAllCombi(dict, searchList);
    
    // 2nd method (trie method)
    ds.trieMethod(dict, searchList);
    
    
    system("pause");
    return 0;
}

