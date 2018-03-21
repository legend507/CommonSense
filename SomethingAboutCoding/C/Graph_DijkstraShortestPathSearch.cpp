/*
Dijkstra’s algorithm
这个用于寻找weighted graph中从src到各个vertex的最短路径
想法是，用一个sptSet来记录某个vertex是否已经processed，以及一个dict来记录从src到vertex i的最短距离

从src开始，
先寻找和src直连的vertex，记录dist，标记为processed
然后再寻找和这些直连vertex直连的vertex
*/

#include <vector>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <stack>
using namespace std;

template <typename T>
using matrix = vector<vector<T>>;

struct Path {
	int parentNode;
	Path() :parentNode(-1) {}
};

class Dijsktra {
	int vertex = 9;	// # of nodes in a graph

public:
	int minDistance(vector<int>& dist, vector<bool>& sptSet) {
		int min = INT_MAX;
		int minIndex;

		/*
		dist中保存有现在已知的src到vertex的最短距离，
		下面func返回 */
		for (int i = 0; i < vertex; i++) {
			if (sptSet[i] == false && dist[i] <= min) {
				min = dist[i];
				minIndex = i;
			}
		}
		return minIndex;
	}

	int printResult(vector<int>& dist, vector<Path>& path, int src) {
		cout << "vetex	dist from src(=" << src << ")" << endl;
		for (int i = 0; i < vertex; i++) {
			cout << i << "	" << dist[i] << "	";
			// print path
			printPath(path, src, i);
			cout << endl;
		}
		return 0x00;
	}
	int printPath(vector<Path>& path, int src, int i) {
		if (src == i)	return 0x00;

		stack<int> s;
		int curI = i;
		s.push(curI);
		while (curI != src) {
			s.push(path[curI].parentNode);
			curI = path[curI].parentNode;
		}

		while (!s.empty()) {
			cout << s.top() << " -> ";
			s.pop();
		}
		return 0x00;
	}

	int dijkstra(matrix<int>& graph, int src) {
		// dist[i] will hold the shortest distance from src to i
		vector<int> dist(vertex, INT_MAX);
		dist[src] = 0;

		// to record if vertex is processed 
		vector<bool> sptSet(vertex, false);

		vector<Path> path(vertex);

		for (int count = 0; count < vertex - 1; count++) {
			/*
			取得最小到src距离最小的vertex，在第一次被call时，返回的总是src*/
			int curIndex = minDistance(dist, sptSet);

			sptSet[curIndex] = true;

			/*找到一个已经processed的vertex，从此vertex出发，找与其直连并没有processed的vertex*/
			for (int i = 0; i < vertex; i++) {
				if (!sptSet[i] &&										/*vertex i is not processed yet*/
					graph[curIndex][i] &&								/*there is an edge from vertex curIndex to i*/
					dist[curIndex] != INT_MAX &&						/*there is an path from src to curIndex*/
					dist[curIndex] + graph[curIndex][i] < dist[i]) {	/*src->curIndex->i is shorter than formerly found path src->i*/

					dist[i] = dist[curIndex] + graph[curIndex][i];	// update dist
					path[i].parentNode = curIndex;					// record path curIndx->i
				}
			}
		}
		printResult(dist, path, src);

		return 0x00;
	}
};


int main() {

	/*
	graph[i][j] = distance from vertex i to vertex j, 0 means not connected*/
	matrix<int> graph =
	{
		{ 0, 4, 0, 0, 0, 0, 0, 8, 0 },		/*0*/
		{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },		/*1*/
		{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },		/*2*/
		{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },		/*3*/
		{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },		/*4*/
		{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },	/*5*/
		{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },		/*6*/
		{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },		/*7*/
		{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }		/*8*/
	};
	Dijsktra d;
	d.dijkstra(graph, 0);

	system("pause");
	return 0;
}

