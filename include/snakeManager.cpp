#include "snakeManager.h"

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
bool moveSnake(Snake& snake, Map& gameMap, int dx, int dy) {
    int newX = snake.head->x + dx;
    int newY = snake.head->y + dy;

    // 충돌 검사
    Block* next = gameMap.mapArray[newX][newY];
    if (dynamic_cast<wallBlock*>(next) || 
        dynamic_cast<NonGateWallBlock*>(next) || 
        dynamic_cast<snakeTail*>(next)) {
        return false;  // 게임오버
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
        return false;
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
