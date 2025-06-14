#include "gate.h"

extern std::pair<int, int> gateA, gateB;

void placeGates(Map& gameMap) {
    if (gateInitialized) return;  // 이미 생성된 경우 생략

    std::vector<std::pair<int, int>> wallPositions;

    for (int i = 0; i < gameMap.row; ++i) {
        for (int j = 0; j < gameMap.col; ++j) {
            if (gameMap.map[i][j] == WALL) {
                wallPositions.emplace_back(i, j);
            }
        }
    }

    if (wallPositions.size() < 2) return;

    std::shuffle(wallPositions.begin(), wallPositions.end(), std::mt19937(std::random_device()()));
    gateA = wallPositions[0];
    gateB = wallPositions[1];

    // map 값 수정
    gameMap.map[gateA.first][gateA.second] = GATE;
    gameMap.map[gateB.first][gateB.second] = GATE;

    // mapArray 수정
    delete gameMap.mapArray[gateA.first][gateA.second];
    delete gameMap.mapArray[gateB.first][gateB.second];
    gameMap.mapArray[gateA.first][gateA.second] = new gateBlock("Gate");
    gameMap.mapArray[gateB.first][gateB.second] = new gateBlock("Gate");

    gateInitialized = true;
}