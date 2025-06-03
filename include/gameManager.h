#pragma once

#include "map.h"
#include "snakeManager.h"
#include <chrono>
#include <thread>
#include <ncurses.h>

void gameTickLoop(Map& gameMap, Snake& snake);
