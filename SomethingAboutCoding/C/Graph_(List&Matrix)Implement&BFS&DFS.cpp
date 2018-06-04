/*
Following two are the most commonly used representations of graph.
1. Adjacency Matrix
Matrix比较简单，就是用v代表vertex个数，然后VxV的Matrix[i][j]代表定点i到j有没有edge（weight多少）
2. Adjacency List
V代表定点个数，然后一个list[v]来代表edge，如果list[i]中有j，则i到j有edge
下面func是这个的实装，+BFS
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;

/*
下面的Graph 使用 Adjacent List实装的*/
class GraphList {
	int v;
	list<int> *adj;
public:
	GraphList(int v) {
		this->v = v;
		adj = new list<int>[v];
	}

	void addEdge(int i, int j) {
		adj[i].push_back(j);		// add an edge i -> j
	}

	/*
	Breadth first search & print	*/
	void BFS(int src) {
		// a visited vector serves as an indicator
		vector<bool> visited(v, false);

		// when meet new unvisited vertex, add to toVisit
		list<int> toVisit;

		visited[src] = true;
		toVisit.push_back(src);

		// repeat until toVisit is empty
		while (!toVisit.empty()) {
			int v = toVisit.front();
			toVisit.pop_front();
			cout << v << " ";		// <- print current vertex

									// 看与当前点v相连的所有顶点，如果这些顶点中还有没有visited的，push_back to list
			for (auto i = adj[v].begin(); i != adj[v].end(); i++) {
				if (!visited[*i]) {
					visited[*i] = true;
					toVisit.push_back(*i);
				}
			}
		}
	}
	/*
	Depth first search & print,
	usually, we do NOT DFS on Graph */
	void DFS(int src) {
		vector<int> visited(v, false);

		DFSRecurse(src, visited);
	}
	void DFSRecurse(int v, vector<int>& visited) {
		// base case
		visited[v] = true;
		cout << v << " ";

		// recurse
		for (auto i = adj[v].begin(); i != adj[v].end(); i++) {
			if (!visited[*i])
				DFSRecurse(*i, visited);
		}
	}
};

/*
下面的Class是用Matrix实装的*/
using matrix = vector<vector<int>>;
///这个struct只是个framework
struct vertex {
	int id;
	string info;
	vertex(int x) : id(x), info("") {};
};
class GraphMatrix {
	int v;					// v = how many nodes
	vector<vertex> vNode;	// dummy, if you want to store info of each vertex, use this
	matrix edge;
public:
	GraphMatrix(int v) {
		this->v = v;
		edge.resize(v, vector<int>(v, 0));	// construct VxV matrix filled with 0
	}

	void addEdge(int i, int j, int weight = 1) {
		edge[i][j] = weight;		// 0 = not connected, >0 means weight
	}

	void BFS(int src) {
		vector<bool> visited(v, false);
		queue<int> toVisit;

		toVisit.push(src);
		visited[src] = true;

		while (!toVisit.empty()) {
			int curV = toVisit.front();
			toVisit.pop();
			visited[curV] = true;
			cout << curV << " ";

			for (int j = 0; j < v; j++) {
				if (edge[curV][j] != 0 &&
					!visited[j]) {
					toVisit.push(j);
				}
			}
		}
	}

	void DFS(int src) {
		vector<bool> visited(v, false);

		DFSRecurse(src, visited);
	}
	void DFSRecurse(int i, vector<bool>& visited) {
		// base case, meet a new node, set it to visited and print value
		visited[i] = true;
		cout << i << " ";

		// recurse case, traverse this new node's edges
		for (int j = 0; j < v; j++) {
			if (edge[i][j] != 0 &&
				!visited[j]) {
				DFSRecurse(j, visited);
			}
		}
	}
};

int main(int argc, const char * argv[]) {
	GraphMatrix g(4);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(3, 3);

	g.DFS(2);

	system("pause");
	return 0;
}
