/*
To approximate the shortest path in real-life situations, like- in maps, games where there can be many hindrances.

We can consider a 2D Grid having several obstacles and we start from a source cell (coloured red below) to reach towards a goal cell (coloured green below)

A*PathFinding

What is A* Search Algorithm?
A* Search algorithm is one of the best and popular technique used in path-finding and graph traversals.

Why A* Search Algorithm ?
Informally speaking, A* Search algorithms, unlike other traversal techniques, it has “brains”. What it means is that it is really a smart algorithm which separates it from the other conventional algorithms. This fact is cleared in detail in below sections.
And it is also worth mentioning that many games and web-based maps use this algorithm to find the shortest path very efficiently (approximation).
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

typedef pair<int, int>	iiPair;
typedef pair<double, pair<int, int>> diiPair;

template <typename T>
using matrix = vector<vector<T>>;

struct cell {
	int parent_i;	// from (parent_i,parent_j) to (i,j) 
	int parent_j;	// 
	double f;	// f = g + h, 
	double g;	// physical distance from (i,j) to (i',j') or Euclid Dist
	double h;	// a so-called "heuristic", Euclid Dist from (i,j) to Destination

				// operator overload ==
	inline bool operator==(const cell& cell) {
		return (cell.parent_i == parent_i && cell.parent_j == parent_j);
	}

	cell() :parent_i(-1), parent_j(-1), f(FLT_MAX), g(FLT_MAX), h(FLT_MAX) {};
};

class AStartSearch {
private:
	int ROW = 9;
	int COL = 10;

	/*
	当前(row,col)是否超界
	*/
	bool isCoordinateValid(int row, int col) {
		return (row >= 0 && row < ROW &&
			col >= 0 && col < COL);
	}
	/*
	grid中当前cell是否是blocked
	*/
	bool isCellBlocked(matrix<int> grid, int row, int col) {
		/*grid的当前cell为0时，代表blocked*/
		if (grid[row][col] == 0)	return true;
		else						return false;
	}
	/*
	A func to check if current(row,col) is destination
	*/
	bool isDestination(int row, int col, iiPair& dest) {
		if (row == dest.first && col == dest.second)	return true;
		else											return false;
	}
	/*计算H值，
	H值的定义是，当前cell到dest的直线距离，
	用这个值作为一个向导，来估计大概*/
	double calcHValue(int row, int col, iiPair dest) {
		return (
			(double)sqrt((row - dest.first)*(row - dest.first) + (col - dest.second)*(col - dest.second))
			);
	}

	int printPath(matrix<cell>& cellDetail, iiPair& src, iiPair& dest) {
		int nextI = dest.first;
		int nextJ = dest.second;
		int srcI = src.first;
		int srcJ = src.second;
		stack<iiPair> s;

		while (nextI != srcI || nextJ != srcJ) {
			s.push({ nextI, nextJ });
			int curI = nextI;
			int curJ = nextJ;
			nextI = cellDetail[curI][curJ].parent_i;
			nextJ = cellDetail[curI][curJ].parent_j;
		}
		s.push({ srcI,srcJ });

		while (!s.empty()) {
			iiPair curPair = s.top();
			s.pop();
			cout << "(" << curPair.first << "," << curPair.second << ")" << " -> ";
		}

		return 0x00;
	}

public:
	/*
	主func，从src的8个相邻cell开始，直到找到dest为止
	用closedList来记录visited or not
	用openList来记录还有哪个点要去
	(想法和Graph的遍历很相似)*/
	int process(matrix<int> grid, iiPair src, iiPair dest) {
		// check if src valid, blocked
		// check if dest valid, blocked
		// check if src == dest
		//	omit

		// a closed list to indicate if a cell in included，可以考虑成来标记visited的matrix
		matrix<bool> closedList(ROW, vector<bool>(COL, false));

		// a cellDetail matrix to store all detail of a specific cell
		matrix<cell> cellDetail(ROW, vector<cell>(COL));
		///	put src cell info in
		cellDetail[src.first][src.second].f = 0.0;
		cellDetail[src.first][src.second].g = 0.0;
		cellDetail[src.first][src.second].h = 0.0;
		cellDetail[src.first][src.second].parent_i = src.first;
		cellDetail[src.first][src.second].parent_j = src.second;

		// an open list, <f, <row,col>>, where f = g+h
		///	set only allows Unique Elemet
		set<diiPair> openList;
		/// add src cell to openList
		openList.insert({ 0.0,{ src.first, src.second } });

		bool foundDest = false;

		while (!openList.empty()) {
			// get one element from openList
			diiPair curPair = *openList.begin();
			openList.erase(curPair);

			int i = curPair.second.first;
			int j = curPair.second.second;
			//关于closedList，按以下方式理解
			//	在第一个while，src被设为True，被移除openList；同时，src周围的8个cell被放入openList
			//	然后几次while把这8各点依次设为true，然后把8各点周围的点放到openList
			closedList[i][j] = true;

			/*
			Generating all the 8 successor of this cell

			N.W   N   N.E
			\   |   /
			\  |  /
			W----Cell----E
			/ | \
			/   |  \
			S.W    S   S.E

			Cell-->Popped Cell (i, j)
			N -->  North       (i-1, j)
			S -->  South       (i+1, j)
			E -->  East        (i, j+1)
			W -->  West           (i, j-1)
			N.E--> North-East  (i-1, j+1)
			N.W--> North-West  (i-1, j-1)
			S.E--> South-East  (i+1, j+1)
			S.W--> South-West  (i+1, j-1)*/

			/*
			nextI = i-1, i, i+1
			nextJ = j-1, j, j+1
			Don't check(i,j), there are 8 combinations	*/
			for (int nextI = i - 1; nextI <= i + 1; nextI++) {
				for (int nextJ = j - 1; nextJ <= j + 1; nextJ++) {
					if (nextI == i && nextJ == j)	continue;

					// proceed only when (nextI,nextJ) is valid, and not the same (i,j)
					if (isCoordinateValid(nextI, nextJ)) {
						// if (nextI,nextJ) is destination
						if (isDestination(nextI, nextJ, dest)) {
							cellDetail[nextI][nextJ].parent_i = i;
							cellDetail[nextI][nextJ].parent_j = j;
							cout << "reached Destination !!" << endl;
							printPath(cellDetail, src, dest);
							foundDest = true;
							return 0x00;
						}
						// if not destination
						///	do if current cell is NOT blocked and NOT already in closedList
						else if (!closedList[nextI][nextJ] &&
							!isCellBlocked(grid, nextI, nextJ)) {
							// update g, h, f
							/// for g, go across diagno is more costly, hence 1.414
							double gNew = cellDetail[i][j].g +
								abs(nextI - i) + abs(nextJ - j) > 1 ? 1.414 : 1.0;
							double hNew = calcHValue(nextI, nextJ, dest);
							double fNew = gNew + hNew;

							// use f as indicator of GOOD (smaller is GOOD)
							//	if found a better way to go to current cell
							//	update cellDetail of this cell
							if (cellDetail[nextI][nextJ].f > fNew) {
								// add (nextI,nextJ) to openList, waiting to be processed
								openList.insert({ fNew,{ nextI, nextJ } });

								//
								cellDetail[nextI][nextJ].f = fNew;
								cellDetail[nextI][nextJ].g = gNew;
								cellDetail[nextI][nextJ].h = hNew;
								cellDetail[nextI][nextJ].parent_i = i;
								cellDetail[nextI][nextJ].parent_j = j;
							}
						}
					}
				}
			}
		}
		if (!foundDest) {
			cout << "No Path Found" << endl;
		}
		return 0x00;
	}
};


int main() {
	/* Description of the Grid-
	1--> The cell is not blocked
	0--> The cell is blocked    */
	matrix<int> grid =
	{
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
	};

	AStartSearch as;
	as.process(grid, { 8,0 }, { 0, 0 });

	system("pause");
	return 0;
}

