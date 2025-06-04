#pragma once

#include "block.h"
#include "./map.h"
#include <deque>
#include <utility>

struct Snake {
    std::deque<std::pair<int, int>> body;   // Tail 위치
    snakeHead* head = nullptr;              // Head 포인터
    int length = 3;                         // 기본 길이(Head+Tail)
};
