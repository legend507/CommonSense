/*
Given an square matrix, turn it by 90 degrees in anti-clockwise direction without using any extra space.

Examples:

Input
 1  2  3
 4  5  6
 7  8  9

Output:
 3  6  9 
 2  5  8 
 1  4  7 

Input:
 1  2  3  4 
 5  6  7  8 
 9 10 11 12 
13 14 15 16 

Output:
 4  8 12 16 
 3  7 11 15 
 2  6 10 14 
 1  5  9 13
*/
#include    <vector>
#include    <iostream>
using namespace std;

template<typename T>
class Solution {
public:
    int turn90Clockwise(vector<vector<T>>& aMatrix) {
        int row = aMatrix.size();
        int col = aMatrix[0].size();
        if(row != col)  return 0x01;    // not square matrix error

        // loop the layer, e.g., a 3x3 matrix has 1 layers, a 4x4 matrix has 2 layers to rotate...
        //  example: row=col=4, x=0(y=0,1,2), x=1(y=1), x markes layers
        for(int x = 0; x < col/2; x++) {

            // loop the col 
            for(int y = x; y < col-1-x; y++) {
                T temp = aMatrix[x][y];

                aMatrix[x][y]               = aMatrix[col-1-y][x];
                aMatrix[col-1-y][x]         = aMatrix[col-1-x][col-1-y];
                aMatrix[col-1-x][col-1-y]   = aMatrix[y][col-1-x];
                aMatrix[y][col-1-x]         = temp;
            }
        }

        return 0;
    }

    int turn90AntiClockwise(vector<vector<T>>& aMatrix) {
        int row = aMatrix.size();
        int col = aMatrix[0].size();
        if(row != col)  return 0x01;    // not square matrix error

        for(int x = 0; x < col/2; x++) {
            for(int y = x; y < col-1-x; y++) {
                T temp = aMatrix[x][y];

                aMatrix[x][y]               = aMatrix[y][col-1-x];
                aMatrix[y][col-1-x]         = aMatrix[col-1-x][col-1-y];
                aMatrix[col-1-x][col-1-y]   = aMatrix[col-1-y][x];
                aMatrix[col-1-y][x]         = temp;
            }
        }

        return 0;
    }

    int printMatrix(vector<vector<T>>& aMatrix) {
        int row = aMatrix.size();
        int col = aMatrix[0].size();

        for(int i=0; i<row;i++){
            for(int j=0;j<col;j++) {
                cout << aMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "---------------" << endl;
        return 0;
    }

};

int main() {
    vector<vector<char>> input = {
        {'a','a','a','a'},
        {'b','b','b','b'},
        {'c','C','c','c'},
        {'d','d','d','d'},
    };

    Solution<char> sol;
    sol.printMatrix(input);

    sol.turn90Clockwise(input);

    sol.printMatrix(input);
    
    sol.turn90AntiClockwise(input);

    sol.printMatrix(input);

    return 0;

}
