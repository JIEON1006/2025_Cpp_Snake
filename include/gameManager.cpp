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
                mvprintw(0, 0, "Game Over!");
                refresh();
                break;
            }

            // 화면 갱신
            clear();
            for (int i = 0; i < gameMap.row; ++i)
                for (int j = 0; j < gameMap.col; ++j)
                    gameMap.mapArray[i][j]->print();
            refresh();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
