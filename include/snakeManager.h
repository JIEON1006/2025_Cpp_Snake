#pragma once

#include "block.h"
#include "map.h"
#include "snake.h"
#include <deque>
#include <utility>

void initSnake(Snake& snake, Map& gameMap);
bool moveSnake(Snake& snake, Map& gameMap, int dx, int dy);
void renderMap(const Map& gameMap);