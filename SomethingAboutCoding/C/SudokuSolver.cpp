
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <windows.h>
using namespace std;

struct OneCell {
	int row;
	int col;
	int hasFinished;

	OneCell(int x, int y) : row(x), col(y), hasFinished(0) {}
};

class SodokuSolver {
	vector<vector<int>> missingCell;
	vector<OneCell> missingCoord;
	vector<vector<int>> matrix;
	int n;	// size

			// check if it is OK to put [num] in matrix[row][col]
			//	1. matrix[?][col]	doesNOT have a same num
			//	2. matrix[row][?]	doesNot have a same num
	bool isNumInCellOK(int row, int col, int num) {

		// check column first
		for (int i = 0; i < n; i++) {
			if (matrix[i][col] == num || missingCell[i][col] == num) {
				return false;
			}
		}
		// check row 
		for (int j = 0; j < n; j++) {
			if (matrix[row][j] == num || missingCell[row][j] == num) {
				return false;
			}
		}

		return true;
	}

public:
	int process(const vector<vector<int>>& input) {
		matrix = input;
		n = matrix.size();
		missingCell.resize(n, vector<int>(n, 0));

		// input matrix 的空格用0表示，如果找到0，就把missingCell的对应格子变成1，并且保存此cell坐标
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				if (matrix[row][col] == 0) {
					missingCoord.push_back(OneCell(row, col));
				}
			}
		}

		// traverse all coordinates 
		//	row = missingCoord[i].row
		//	col = missingCoord[i].col
		for (int i = 0; i < missingCoord.size();) {

			int curRow = missingCoord[i].row;
			int curCol = missingCoord[i].col;
			int curNum = missingCell[curRow][curCol];	// start from 0
			bool found = false;

			for (curNum = curNum + 1; curNum < 10; curNum++) {

				if (isNumInCellOK(curRow, curCol, curNum)) {
					missingCell[curRow][curCol] = curNum;
					found = true;
					break;
				}
			}

			if (found)
				i++;
			else {
				// traversed 1~9 in this cell, didn't find a solution, go back to former cell,
				//	and 0 clear this cell
				i--;
				missingCell[curRow][curCol] = 0;
			}

			printMatrix();

		}
		return 0;
	}

	void printMatrix() {
		Sleep(10);

		system("CLS");
		cout << "BackTracing:" << endl;

		int width = 3;
		cout << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] != 0) {
					cout << right << setw(width) << matrix[i][j];
				}
				else if (missingCell[i][j] != 0) {
					cout << right << setw(width) << missingCell[i][j];
				}
				else {
					cout << right << setw(width) << "-";
				}

			}
			cout << endl;
		}
		cout << "------------" << endl;

	}

};

int main() {
	SodokuSolver sds;

	vector<vector<int>> input = {
		{ 3,0,6,5,0,8,4,0,0 },
	{ 5,2,0,0,0,0,0,0,0 },
	{ 0,8,7,0,0,0,0,3,1 },
	{ 0,0,3,0,1,0,0,8,0 },
	{ 9,0,0,8,6,3,0,0,5 },
	{ 0,5,0,0,9,0,6,0,0 },
	{ 1,3,0,0,0,0,2,5,0 },
	{ 0,0,0,0,0,0,0,7,4 },
	{ 0,0,5,2,0,6,3,0,0 }

	/*	{3,1,6,5,7,8,4,9,2},
	{5,2,9,1,3,4,7,6,8},
	{4,8,7,6,2,9,5,3,1},
	{2,6,3,4,1,5,9,8,7},
	{9,7,4,8,6,3,1,2,5},
	{8,5,1,7,9,2,6,4,3},
	{1,3,8,9,4,7,2,5,6},
	{6,9,2,3,5,1,8,7,4},
	{7,4,5,2,8,6,3,1,9}
	*/
	};

	sds.process(input);

	system("pause");
	return 0;
}