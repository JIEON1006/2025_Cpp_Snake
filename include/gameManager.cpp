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

                int centerY = LINES / 2;
                int centerX = (COLS - 18) / 2;

                attron(A_BOLD);
                attron(COLOR_PAIR(3));
                mvprintw(centerY - 1, centerX, "===================");
                mvprintw(centerY,     centerX, "   GAME  OVER!    ");
                mvprintw(centerY + 1, centerX, "===================");
                attroff(COLOR_PAIR(3));
                attroff(A_BOLD);

                mvprintw(centerY + 3, centerX, "Press any key to exit...");
                refresh();

                nodelay(stdscr, FALSE); // 입력 대기 모드로 전환
                getch();                // 사용자 키 입력 대기
                break;
            }

            // 화면 갱신
            clear();
            for (int i = 0; i < gameMap.row; ++i) {
                for (int j = 0; j < gameMap.col; ++j) {
                    int value = gameMap.map[i][j];

                    // 색상 기본값: 흰색 (colorPair 1)
                    int colorPair = 1;

                    // 스네이크 머리 또는 몸통일 경우만 초록색
                    if (value == SNAKE_HEAD || value == SNAKE_BODY) {
                        colorPair = 2;
                    }

                    printColoredBlock(i, j, gameMap.mapArray, colorPair);
                }
            }
            refresh();

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
