/*
Google Interview Question
 Given a sorted dictionary (array of words) of an alien language, find order of characters in the language.
 
 Examples:
 
 Input:  words[] = {"baa", "abcd", "abca", "cab", "cad"}
 Output: Order of characters is 'b', 'd', 'a', 'c'
 Note that words are sorted and in the given language "baa"
 comes before "abcd", therefore 'b' is before 'a' in output.
 Similarly we can find other orders.
 
 Input:  words[] = {"caa", "aaa", "aab"}
 Output: Order of characters is 'c', 'a', 'b'

以下解法非我原创，不过非常有参考价值，特别是graph的创建方法
 解释一下思想：
 0. check不同字母个数，construct一个graph，根据不同字母个数建立节点
 1. 比较word[i]和word[i+1]的每一对应letter，如果看到一个不同，就在graph的那两个定点上add edge，edge的方向是 先出现的letter -> 后出现的letter
 (通过以上两步可以得到一个包含所有信息的graph)
 2. 遍历graph，发现最不重要的node，消除，然后重复	<- 这个递归方法很有参考价值
 */

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <stack>
using namespace std;

// A BST node
struct node
{
    int data;
    node* left, *right;
    
    node(int x) : data(x), left(NULL), right(NULL) {}
};

class Graph {
public:
    int v;
    list<int> *adj;
    
    Graph(int v) {
        this->v = v;
        adj = new list<int>[v];
    }
    
	// add an edge v -> w (the edge has direction!!)
    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }
    
	void topologicalSort() {
		stack<int> s;
		bool *visited = new bool[v];
		for (int i = 0; i < v; i++)
			visited[i] = false;

		// recursively push all nodes into stack
		for (int i = 0; i < v; i++) {
			if (visited[i] == false) {
				topologicalSortUtil(i, visited, s);
			}
		}

		// print
		while (!s.empty()) {
			cout << (char)('a' + s.top()) << "->";
			s.pop();
		}
		cout << endl;
	}

	/*
	topological sort func, this func removes the "least significant node" (the node does not pointing to any other node)
	and then remove the next least significant node, ..., until there is only one node left
	*/
    void topologicalSortUtil(int i, bool visited[], stack<int>& s) {
		visited[i] = true;

		for (auto itr = adj[i].begin(); itr != adj[i].end(); itr++)
			// if hasn't visited yet
			if (!visited[*itr])
				topologicalSortUtil(*itr, visited, s);	
		
		// if i has no edge pointing to other node
		s.push(i);
    }
    
    void printGraph() {
        for(int i = 0; i < v; i++) {
			cout << "[" << i << "] -> ";
            for(auto itr=adj[i].begin(); itr != adj[i].end(); itr++) {
                cout << *itr << " ";
            }
            cout << endl;
        }
    }
    
};

class AlienDict {
public:
    void process(vector<string>& words) {

		// 1st, find all distinctive letter 
        unordered_map<char, int> record;
        for(auto oneWord:words) {
            for(int i = 0; i < oneWord.size(); i++) {
                record[oneWord[i]] = (int)oneWord[i];
            }
        }
        
        int allLetters = (int)record.size();
        Graph g(allLetters);
        
		// 2nd, compare every word with next word, add edges
        for(int i = 0; i < words.size()-1; i++) {
            string word1 = words[i];
            string word2 = words[i+1];
            
            for(int j = 0; j < min(word1.size(), word2.size()); j++) {
                if(word1[j] != word2[j]) {
					// if adj[2] = 1 (2 means 'c', 1 means 'b'), then c is prior than b
                    cout << "adj[" << word1[j]-'a' << "]=" <<word2[j]-'a' << endl;
                    g.addEdge(word1[j]-'a', word2[j]-'a');
                    break;
                }
            }
        }
		g.topologicalSort();
    }
};

int main() {
    
    vector<string> words = { "caa",
        "aaa",
        "aab" };
    AlienDict ad;
    ad.process(words);
    
	system("pause");
    return 0;
}
