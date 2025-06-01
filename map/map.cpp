#include "block.h"
#include "map.h"
#include <ncurses.h>
#include <fstream>
#include <sstream>

Map::Map() { //map.txt로 부터 읽어와 정수로 이루어진 map 벡터를 초기화하고 -> 각 벡터의 원소를 
    loadFromFile("./map.txt");
}

Map::~Map() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            delete mapArray[i][j];
        }
    }
}

void Map::initMap() { //공백과 벽으로 이루어진 정수형 map 배열 생성
    row = MAP_ROW;
    col = MAP_COL;
    for (int i = 0; i < MAP_ROW; ++i) {
        for (int j = 0; j < MAP_COL; ++j) {
            if (i == 0 || i == MAP_ROW - 1 || j == 0 || j == MAP_COL - 1) {
                map[i][j] = WALL;
            } else {
                map[i][j] = EMPTY;
            }
        }
    }
}

void Map::loadFromFile(const std::string& filename) { //map.txt를 읽어와서 map(정수 2차원 벡터)를 채우고, 정수를 문자로 매핑 mapArray(2차원 벡터)
    
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "[Error] Cannot open map file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    map.clear();  // 이전 내용이 있을 경우 초기화

    // 1. 파일로부터 한 줄씩 읽어 정수 맵 구성
    while (std::getline(file, line)) {
        std::vector<int> rowVec;
        for (char ch : line) { 
            if (isdigit(ch)) rowVec.push_back(ch - '0'); 
        }
        if (!rowVec.empty()) map.push_back(rowVec); //읽은 문자열을 한 글자씩 보면서 rowVec에 저장

    }

    if (map.empty()) {
        std::cerr << "[Error] Map file is empty or invalid format." << std::endl;
        exit(1);
    }

    row = map.size(); //map.txt로 부터 행 크기 읽어오기
    col = map[0].size(); //map.txt로 부터 열 크기 읽어오기
    mapArray.resize(row, std::vector<Block*>(col, nullptr)); //map.txt에서 읽어와서 mapArray 사이즈 재할당

    auto tempBlockArray = createBlockMatrix(map); //정수를 문자로 매핑

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            mapArray[i][j] = tempBlockArray[i][j];
        }
    }
}

void Map::printMap() { //for문을 돌며 블록 단위로 맵 출력
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            printBlockAt(i, j, mapArray);
        }
    }
    refresh();
}

void Map::printColoredMap() { //for문을 돌며 블록 단위로 맵 출력 -> 블록 요소의 색은 여기서 정의, colorPair는 main.cpp에서 정의
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int value = map[i][j];   // 정수형 맵 값
            int colorPair = 1;       // 기본 색상

            // 정수값에 따라 색상 선택
                switch (value) {
                case SNAKE_BODY:      colorPair = 2; break;
                case WALL:            colorPair = 3; break;
                case IMMUNE_WALL:     colorPair = 4; break;
                case GATE:            colorPair = 5; break;
                case GROWTH_ITEM:     colorPair = 6; break;
                case MINUS_ITEM:      colorPair = 7; break;
                default:              colorPair = 1; break;  // EMPTY, 기타 값
            }

            printColoredBlock(i, j, mapArray, colorPair);
        }
    }
    refresh();
}


int getMapValue(int x, int y,  const vector<vector<int>>& map) {
    
    if (map.empty()) return -1; // 맵 자체가 비어 있으면 접근 금지

    if (x >= 0 && static_cast<size_t>(x) < map.size()) {
        if (y >= 0 && static_cast<size_t>(y) < map[x].size()) {
            return map[x][y];
        }
    }      
    return -1;
}



vector<vector<Block*>> createBlockMatrix(const vector<vector<int>>& intMatrix) {
    int rows = intMatrix.size();
    int cols = rows > 0 ? intMatrix[0].size() : 0;

    vector<vector<Block*>> blockMatrix(rows, vector<Block*>(cols, nullptr));  // 포인터 2차원 배열

    for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
        int value = getMapValue(row,col, intMatrix);

            //type에 따라 다른 Block 서브클래스 객체(동적 할당)를 생성
            if (value == 0)
                blockMatrix[row][col] = new blankBlock("blank");
            else if (value == 1)
                blockMatrix[row][col] = new wallBlock("wall");
            else if (value == 2)
                blockMatrix[row][col] = new NonGateWallBlock("NonGate");

            /* 나머지 클래스 필요하면 차후에 추가 */
        
        }
    }
    return blockMatrix;
}


void destroyBlockMatrix(std::vector<std::vector<Block*>>& matrix) {
    for (auto& row : matrix) {
        for (Block* b : row) {
            delete b;
        }
    }
}
