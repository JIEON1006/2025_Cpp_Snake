#pragma once

#include "map.h"
#include "snakeManager.h"
#include "start_screen.h"
#include <chrono>
#include <thread>
#include <ncurses.h>

void gameTickLoop(Map& gameMap, Snake& snake);
