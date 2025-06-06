#pragma once

#include "map.h"
#include "snakeManager.h"
#include "screen.h"
#include "itemManager.h"
#include <chrono>
#include <thread>
#include <ncurses.h>

void gameTickLoop(Map& gameMap, Snake& snake);