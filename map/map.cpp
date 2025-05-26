#include "map.h"
#include "constant.h"
#include <iostream>
#include <vector>

class Map {
public:
    /// Map 클래스의 구성 요소 
    int row, col;
    vector<vector<Block*>> mapArray[row][col];   //Block으로 채워진 map array 
    void printMap(){                    //Block mapArray을 프린트하는 함수
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                cout << mapArray.print();
            }
            cout << endl;
        }
    }
};

//int 2차원 배열을 받아서 같은 크기의 Block 클래스 2차원 배열로 변환하는 동적 배열 함수 + 배열의 원소 객체까지 생성하는 함수 
vector<vector<Block*>> createBlockMatrix(const vector<vector<int>>& intMatrix) {
    int rows = intMatrix.size();
    int cols = rows > 0 ? intMatrix[0].size() : 0;

    vector<vector<Block*>> blockMatrix(rows, vector<Block*>(cols, nullptr));  // 포인터 2차원 배열

    for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
        int value = intMatrix[row][col];

            //type에 따라 다른 Block 서브클래스 객체(동적 할당)를 생성
            if (type == 0)
                blockMatrix[row][col] = new blankBlock();
            else if (type == 1)
                blockMatrix[row][col] = new wallBlock();
            else if (type == 2)
                blockMatrix[row][col] = new NonGateWallBlock();

            /* 나머지 클래스 필요하면 차후에 추가 */
        }
    }
    return blockMatrix;
}

//동적 배열 해제 함수: stage 전환 시 반드시 사용할 것
void destroyBlockMatrix(vector<vector<Block*>>& matrix) {
    for (auto& row : matrix) {
        for (Block* b : row) {
            delete b;
        }
    }
}
