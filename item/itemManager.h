#pragma once
#include "map/map.h"
#include "snake/snake.h"
#include "item.h"
#include <vector>

using namespace std;

class itemManager {
public:

    std::vector<Item> data;  // 기존 activeItems -> data로 통일
    void DeleteCollisionData(int y, int x, Map& gameMap);
    void PositionItem(int x, int y, std::string type, std::chrono::steady_clock::time_point time);
    void PushData(Map& gameMap);  // map에 아이템을 블록으로 반영
    void spawnItems(Map& gameMap);  // 아이템 생성

    void removeExpiredItems(Map& gameMap);             // 시간 지난 아이템 제거
    void applyItemEffect(Snake& snake, Map& gameMap, int x, int y,
                         int& snakeIntervalMs,
                         std::chrono::steady_clock::time_point& speedEndTime);

private:
    const int MAX_ITEMS = 3;
    const int LIFESPAN_MS = 5000;
};
