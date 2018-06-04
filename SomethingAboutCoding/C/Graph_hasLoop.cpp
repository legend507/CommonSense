/*
Google Interview Qs

Course Schedule
There are a total of n courses you have to take, labeled from 0 to n-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

Example 1:

Input: 2, [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: 2, [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you should
also have finished course 1. So it is impossible.
Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

把所有courses存在一个graph里，然后这个问题就转换成为找graph中有没有loop的问题
*/
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <stack>
using namespace std;

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

	/*entrance to a recursive func, detect if there are loops (cycles) in a graph
	这个方法需要死记硬背一下...
	与DFS不同，没有src，而是对于所有v，都check*/
	bool hasLoop() {
		vector<bool> visited(v, false);		// mark if vertex is visited
		vector<bool> recStack(v, false);	// doing DFS from a vertex, this vector is to record if 

		for (int i = 0; i < v; i++) {
			// i是起点，对于每个起点，check有无loop，有一个有的话就返回true
			if (hasLoop_util(i, visited, recStack))	return true;
		}
		return false;
	}

	bool hasLoop_util(int v, vector<bool>& visited, vector<bool>& recStack) {
		// if a vertex is not visited
		if (visited[v] == false) {
			visited[v] = true;
			recStack[v] = true;

			// check all edges from this vertex
			for (auto iter = adj[v].begin(); iter != adj[v].end(); iter++) {
				// recursive, DFS, if the other end of edge is not visited, go to that vertex
				if (!visited[*iter] && hasLoop_util(*iter, visited, recStack))	return true;
				// if recStack[idx] is true, means came back to a formerly visited vertex, so there is a loop
				else if (recStack[*iter]) return true;
			}
		}
		// after checking all edges from a vertex but still NOT found a loop, 
		recStack[v] = false;
		return false;
	}

};

class Solution {
public:
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		Graph g(numCourses);

		for (auto oneEle : prerequisites) g.addEdge(oneEle.first, oneEle.second);

		if (g.hasLoop())	return false;
		else	return true;

	}
};


int main() {
	Solution s;
	vector<pair<int, int>> pre = { {1,0}, {0,1} };

	s.canFinish(3, pre);

	system("pause");
	return 0;

}
