#pragma once

#include "block.h"
#include "Map.h"
#include <deque>
#include <utility>

struct Snake {
    std::deque<std::pair<int, int>> body;   // Tail 위치
    snakeHead* head = nullptr;              // Head 포인터
    int length = 3;                         // 기본 길이
};

void initSnake(Snake& snake, Map& gameMap);
bool moveSnake(Snake& snake, Map& gameMap, int dx, int dy);
void renderMap(const Map& gameMap);
