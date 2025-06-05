#pragma once

#include "block.h"
#include <vector>
#include <string>

#define MAP_ROW 100     // 맵 최대 행 크기
#define MAP_COL 100     // 맵 최대 열 크기

extern std::pair<int, int> gateA, gateB;
extern bool gateInitialized;


// Map 구성 요소 정의
enum MapElement {
    EMPTY = 0,
    WALL = 1,
    IMMUNE_WALL = 2, // 모서리 벽
    SNAKE_HEAD = 3,
    SNAKE_BODY = 4,
    GATE = 5,
    GROWTH_ITEM = 6,
    MINUS_ITEM = 7, // 변수명 minus로 할지 poison으로 할지 말씀드리기
};

class Map {
public:
    int row, col;                                       // 로드된 맵의 행, 열 크기
    std::vector<std::vector<int>> map;                  // 정수형 맵 정보
    std::vector<std::vector<Block*>> mapArray;          // Block 포인터 기반 시각화용 맵

    Map();                                              // 생성자: map.txt 로딩 및 mapArray 초기화
    ~Map();                                             // 소멸자: 동적 메모리 해제

    void initMap();                                     // 공백과 벽으로 초기화된 기본 맵 생성
    void loadFromFile(const std::string& filename);     // map.txt로부터 맵 로딩

    void printMap();                                     // 전체 맵 출력 (색상 없음)
    void printColoredMap();                              // 전체 맵 출력 (색상 있음)
};

// 외부 유틸 함수
int getMapValue(int x, int y, const std::vector<std::vector<int>>& map);  // 좌표의 정수 값 반환

//int 2차원 배열을 받아서 같은 크기의 Block 클래스 2차원 배열로 변환하는 동적 배열 함수 + 배열의 원소 객체까지 생성하는 함수 
std::vector<std::vector<Block*>> createBlockMatrix(const std::vector<std::vector<int>>& intMatrix); // 정수 → Block 배열 변환

//동적 배열 해제 함수: stage 전환 시 반드시 사용할 것
void destroyBlockMatrix(std::vector<std::vector<Block*>>& matrix);  // 동적 Block 배열 메모리 해제
