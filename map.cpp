#include <iostream>
#include <vector>

using namespace std;

// Map의 크기는 변수로 정의해서 바꾸기 쉽게.
// const.h에서 라인 수정하기.

// Map 구성 요소 정의
enum MapElement {
    EMPTY = 0,
    WALL = 1,
    IMMUNE_WALL = 2, // 모서리 벽
    SNAKE_HEAD = 3,
    SNAKE_BODY = 4,
    GATE = 5
    GROWTH_ITEM = 6,
    MINUS_ITEM = 7, // 변수명 minus로 할지 poison으로 할지 말씀드리기
    SPEED_UP = 8,
    DOUBLE_UO = 9,
};

// 2차원 map 배열 정의
int map[MAP_X][MAP_Y];

// map 초기화 함수 (기본 벽과 빈 공간)
void initMap() {
    for (int i = 0; i < MAP_X; ++i) {
        for (int j = 0; j < MAP_Y; ++j) {
            if (i == 0 || i == MAP_X - 1 || j == 0 || j == MAP_Y - 1) {
                map[i][j] = WALL; // 테두리는 벽
            } else {
                map[i][j] = EMPTY;
            }
        }
    }

}

// map 출력 함수
void printMap() {
    for (int i = 0; i < MAP_X; ++i) {
        for (int j = 0; j < MAP_Y; ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

// 특정 위치의 map 값 읽기
int getMapValue(int x, int y) {
    if (x >= 0 && x < MAP_X && y >= 0 && y < MAP_Y) {
        return map[x][y];
    } else {
        return -1; // 범위 초과 시 오류
    }
}


