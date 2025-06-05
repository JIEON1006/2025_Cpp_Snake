#include "gameManager.h"

void gameTickLoop(Map& gameMap, Snake& snake) {
    int dx = -1, dy = 0;  // 초기 방향: 위
    nodelay(stdscr, TRUE);  // getch() 비동기화 
    curs_set(0);

    auto lastTick = std::chrono::steady_clock::now();

    while (true) {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count();

        // 방향키 입력 처리
        int ch = getch();
        switch (ch) {
            case 'w': dx = -1; dy = 0; break;
            case 's': dx = 1; dy = 0; break;
            case 'a': dx = 0; dy = -1; break;
            case 'd': dx = 0; dy = 1; break;
            case 'q': return;  // 종료
            default: break;
        }

        // 1초마다 tick 실행
        if (elapsed >= 1000) {
            lastTick = now;

            if (!moveSnake(snake, gameMap, dx, dy)) {
                
                printGameOverScreen();
                break;
            }

            // 화면 갱신
            clear();

            for (int i = 0; i < gameMap.row; ++i) {
                for (int j = 0; j < gameMap.col; ++j) {

                   Block* block = gameMap.mapArray[i][j];
                    if (dynamic_cast<snakeHead*>(block) || dynamic_cast<snakeTail*>(block)) {
                        printColoredBlock(i, j, gameMap.mapArray, 2); //스네이크는 초록색으로 출력

                    }
                    else if (dynamic_cast<gateBlock*>(block)) {
                        printColoredBlock(i, j, gameMap.mapArray, 5); //게이트는 파란색으로 출력

                    }
                    else{
                        printBlockAt(i,j,gameMap.mapArray); //그 외 구성요소는 일단 흰색으로 출력
                    }
                }
            }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        }
    }
}
