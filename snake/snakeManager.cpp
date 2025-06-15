#include "snakeManager.h"
#include "map.h"
#include "itemManager.h"
#include "screen.h"

//snake 위치 초기화 
void initSnake(Snake& snake, Map& gameMap) {
    int x = gameMap.row;
    int y = gameMap.col;
    int startX = x / 2;
    int startY = y / 2;

    // 기존 블록 제거 후 SnakeHead 배치
    delete gameMap.mapArray[startX][startY];
    snake.head = new snakeHead("Head", startX, startY);
    gameMap.mapArray[startX][startY] = snake.head;
    gameMap.map[startX][startY] = SNAKE_HEAD;

    snake.body.push_back({startX + 1, startY});
    snake.body.push_back({startX + 2, startY});
}


//게임오버 판정용 함수 
bool moveSnake(Snake& snake, Map& gameMap, int& dx, int& dy,
               itemManager* manager,
               int& tickIntervalMs,
               std::chrono::steady_clock::time_point& speedEndTime){
                
    int newX = snake.head->x + dx;
    int newY = snake.head->y + dy;

    // 충돌 검사
    Block* next = gameMap.mapArray[newX][newY];
    if (dynamic_cast<wallBlock*>(next) || 
        dynamic_cast<NonGateWallBlock*>(next)) {
        printGameOverScreen(WALL);
        return false;  // 게임오버
    }
    else if (dynamic_cast<snakeTail*>(next)) {
        printGameOverScreen(BODY);
        return false;  // 게임오버
    }

    // 아이템 효과 먼저 적용
    if (manager) {
        manager->applyItemEffect(snake, gameMap, newX, newY, tickIntervalMs, speedEndTime);
    }

    // 몸 길이 갱신 
    snake.body.push_front({snake.head->x, snake.head->y});
    if ((int)snake.body.size() > snake.length) {
        auto [tx, ty] = snake.body.back();
        snake.body.pop_back();

        delete gameMap.mapArray[tx][ty];
        gameMap.mapArray[tx][ty] = new blankBlock("Blank");
        gameMap.map[tx][ty] = EMPTY;
    }

    // 몸 길이 3 이하일 경우 게임오버
      if (snake.length < 3) {
        printGameOverScreen(LENGTH_UNDER_3);
        return false;
    }

    //머리가 게이트와 닿으면 게이트 이동 실행
    if (gameMap.map[newX][newY] == GATE) {
    std::pair<int, int> current = {newX, newY};
    std::pair<int, int> outGate = (current == gateA) ? gateB : gateA;

    std::pair<int, int> outDir = findExitDirection(outGate, gameMap, dx, dy);
    std::pair<int, int> exit = findExitPosition(outGate, gameMap, outDir);

    if (exit.first == -1) return false;

    newX = exit.first;
    newY = exit.second;
    dx = outDir.first;
    dy = outDir.second;
}


    // 현재 Head 자리를 Tail로 전환
    delete gameMap.mapArray[snake.head->x][snake.head->y];
    gameMap.mapArray[snake.head->x][snake.head->y] = new snakeTail("Tail", snake.head->x, snake.head->y);
    gameMap.map[snake.head->x][snake.head->y] = SNAKE_BODY;

    // 새 Head 생성
    delete gameMap.mapArray[newX][newY];
    snake.head = new snakeHead("Head", newX, newY);
    gameMap.mapArray[newX][newY] = snake.head;
    gameMap.map[newX][newY] = SNAKE_HEAD;

    return true;
}

std::pair<int, int> findExitDirection(std::pair<int, int> gatePos, const Map& gameMap, int inDx, int inDy) {
    int x = gatePos.first;
    int y = gatePos.second;

    // 가장자리 게이트: 맵 안쪽 방향
    if (x == 0) return {1, 0};                       // 상단 → 아래
    if (x == gameMap.row - 1) return {-1, 0};        // 하단 → 위
    if (y == 0) return {0, 1};                       // 좌측 → 오른쪽
    if (y == gameMap.col - 1) return {0, -1};        // 우측 → 왼쪽

    // 가운데 게이트: 진출 가능한 방향 판단
    std::vector<std::pair<int, int>> candidates;

    // 상, 하, 좌, 우
    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };

    for (const auto& dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        if (nx >= 0 && ny >= 0 && nx < gameMap.row && ny < gameMap.col &&
            gameMap.map[nx][ny] == EMPTY) {
            candidates.push_back(dir);
        }
    }

    if (candidates.empty()) return {0, 0};  // 나갈 수 없음

    // 진입 방향 유지 우선
    for (const auto& dir : candidates)
        if (dir == std::make_pair(inDx, inDy)) return dir;

    // 나머지는 규칙 적용
    for (const auto& dir : candidates) {
        if (dir.first == 0) {
            // 좌우 방향
            if ((inDx == -1 || inDy == 1)) return {0, 1};   // 위 or 오른쪽 → 오른쪽
            else return {0, -1};                            // 왼쪽 or 아래 → 왼쪽
        } else if (dir.second == 0) {
            // 상하 방향
            if ((inDx == -1 || inDy == -1)) return {-1, 0};  // 위 or 오른쪽 → 위
            else return {1, 0};                             // 왼쪽 or 아래 → 아래
        }
    }

    return {0, 0};  // fallback
}

std::pair<int, int> findExitPosition(std::pair<int, int> gatePos,
                                     const Map& gameMap,
                                     std::pair<int, int> outDir) {
    int x = gatePos.first;
    int y = gatePos.second;

    int nx = x + outDir.first;
    int ny = y + outDir.second;

    // 벽 충돌 방지
    if (nx >= 0 && ny >= 0 && nx < gameMap.row && ny < gameMap.col &&
        gameMap.map[nx][ny] == EMPTY) {
        return {nx, ny};
    }

    return {-1, -1};  // 나갈 수 없는 위치
}

//gameMap 리로딩 
void renderMap(const Map& gameMap) {
    clear();
    for (int i = 0; i < gameMap.row; ++i) {
        for (int j = 0; j < gameMap.col; ++j) {
            gameMap.mapArray[i][j]->print();
        }
    }
    refresh();
}
