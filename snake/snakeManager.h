#pragma once

#include "block/block.h"
#include "map.h"
#include "snake.h"
#include "itemManager.h"
#include <deque>
#include <utility>

void initSnake(Snake& snake, Map& gameMap);
bool moveSnake(Snake& snake, Map& gameMap, int dx, int dy,
               itemManager* manager,
               int& tickIntervalMs,
               std::chrono::steady_clock::time_point& speedEndTime);
void renderMap(const Map& gameMap);

std::pair<int, int> findExitPosition(std::pair<int, int> gatePos, const Map& gameMap, int inDx, int inDy);
