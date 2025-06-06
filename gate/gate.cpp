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


/*
moveSnake() 내에서 이 findExitPosition()을 호출해서 머리가 게이트에 닿으면 다른 게이트로 나오게 합니다
게이트를 나온 후 방향(Rule4)에 관해선 이 함수를 수정하면 될 것 같습니다!
*/
std::pair<int, int> findExitPosition(std::pair<int, int> gatePos, const Map& gameMap, int inDx, int inDy) {
    int x = gatePos.first;
    int y = gatePos.second;

    // 맵 가장자리인 경우 → 무조건 맵 안쪽 방향
    if (x == 0) return {x + 1, y};  // 상단 벽: 아래
    if (x == gameMap.row - 1) return {x - 1, y};  // 하단 벽: 위
    if (y == 0) return {x, y + 1};  // 좌측 벽: 오른쪽
    if (y == gameMap.col - 1) return {x, y - 1};  // 우측 벽: 왼쪽

    // 가운데 벽인 경우 → 우선순위: 진입 → 시계 → 반시계 → 반대
    std::vector<std::pair<int, int>> directions = {
        {inDx, inDy},               // 진입 방향 유지
        {inDy, -inDx},              // 시계 방향 회전
        {-inDy, inDx},              // 반시계 방향 회전
        {-inDx, -inDy}              // 정반대 방향
    };

    for (const auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;

        if (nx >= 0 && ny >= 0 && nx < gameMap.row && ny < gameMap.col) {
            if (gameMap.map[nx][ny] == EMPTY) {
                return {nx, ny};  // 가능한 방향 발견
            }
        }
    }

    return {-1, -1};  // 나갈 곳이 없음 (예외 처리)
}
