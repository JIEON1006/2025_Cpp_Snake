#pragma once

#include "constant.h"

class Map {
public:
    /// Map 클래스의 구성 요소 
    int row, col;
    vector<vector<Block*>> mapArray[row][col];   //Block으로 채워진 map array
    void printMap(); 
};

vector<vector<Block*>> createBlockMatrix(const vector<vector<int>>& intMatrix);
void destroyBlockMatrix(vector<vector<Block*>>& matrix);