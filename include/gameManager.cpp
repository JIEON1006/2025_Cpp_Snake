#include "gameManager.h"
#include "itemManager.h"
#include <string>

void gameTickLoop(Map& gameMap, Snake& snake) {
    int dx = -1, dy = 0;
    nodelay(stdscr, TRUE);
    curs_set(0);

    auto lastTick = std::chrono::steady_clock::now();
    itemManager manager;

    int tickIntervalMs = 500;
    std::chrono::steady_clock::time_point speedEndTime = std::chrono::steady_clock::now();

    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count();

        int ch = getch();
        switch (ch) {
            case 'w': dx = -1; dy = 0; break;
            case 's': dx = 1; dy = 0; break;
            case 'a': dx = 0; dy = -1; break;
            case 'd': dx = 0; dy = 1; break;
            case 'q': return;
            default: break;
        }

        if (elapsed >= tickIntervalMs) {
            lastTick = now;

            manager.spawnItems(gameMap);
            manager.removeExpiredItems(gameMap);

            if (!moveSnake(snake, gameMap, dx, dy, &manager, tickIntervalMs, speedEndTime)) {
                break;
            }

            // 속도 회복 처리
            if (tickIntervalMs < 500 && now >= speedEndTime) { //속도 조절, tickIntervalMs과 일치해야 함
                tickIntervalMs = 500;
            }

            if (snake.length < 3) {
                printGameOverScreen(LENGTH_UNDER_3);
                break;
            }

            clear();
            for (int i = 0; i < gameMap.row; ++i) {
                for (int j = 0; j < gameMap.col; ++j) {
                    Block* block = gameMap.mapArray[i][j];

                    if (dynamic_cast<snakeHead*>(block) || dynamic_cast<snakeTail*>(block)) {
                        printColoredBlock(i, j, gameMap.mapArray, 2);
                    }
                    else if (dynamic_cast<gateBlock*>(block)) {
                        printColoredBlock(i, j, gameMap.mapArray, 5);
                    }
                    else if (dynamic_cast<itemBlock*>(block)) {
                        printColoredBlock(i, j, gameMap.mapArray, 3);  // 빨간색
                    }
                    else {
                        printBlockAt(i, j, gameMap.mapArray);
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

