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
bool moveSnake(Snake& snake, Map& gameMap, int dx, int dy,
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
    std::pair<int, int> other = (current == gateA) ? gateB : gateA;

    std::pair<int, int> exitDir = findExitDirection(other, gameMap, dx, dy);
    std::pair<int, int> exitPos = findExitPosition(other, exitDir);

    if (exitPos.first == -1) return false;  // 예외 처리

    dx = exitDir.first;
    dy = exitDir.second;

    newX = exitPos.first;
    newY = exitPos.second;
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

    // 가장자리일 경우: 내부 방향 중 유효하고 EMPTY인 방향 선택
    if (x == 0 || x == gameMap.row - 1 || y == 0 || y == gameMap.col - 1) {
        std::vector<std::pair<int, int>> edgeDirs;

        if (x == 0) edgeDirs.push_back({1, 0});  // 아래
        if (x == gameMap.row - 1) edgeDirs.push_back({-1, 0});  // 위
        if (y == 0) edgeDirs.push_back({0, 1});  // 오른쪽
        if (y == gameMap.col - 1) edgeDirs.push_back({0, -1});  // 왼쪽

        for (const auto& dir : edgeDirs) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (nx >= 0 && nx < gameMap.row && ny >= 0 && ny < gameMap.col &&
                gameMap.map[nx][ny] == EMPTY) {
                return dir;
            }
        }
        return {-999, -999};  // 나갈 수 있는 방향 없음
    }

    // 가운데 Gate일 경우: 규칙 적용
    if (inDx == 0) { // 좌우 진입
        return (inDy > 0) ? std::pair<int, int>{0, 1}   // 오른쪽 진입 → 오른쪽
                          : std::pair<int, int>{0, -1}; // 왼쪽 진입 → 왼쪽
    } else {         // 상하 진입
        return (inDx < 0) ? std::pair<int, int>{-1, 0}  // 위 진입 → 위
                          : std::pair<int, int>{1, 0};  // 아래 진입 → 아래
    }
}

std::pair<int, int> findExitPosition(std::pair<int, int> gatePos, std::pair<int, int> outDir) {
    return {gatePos.first + outDir.first, gatePos.second + outDir.second};
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
