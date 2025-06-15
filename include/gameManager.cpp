#include "gameManager.h"
#include "itemManager.h"
#include <string>
#include "Player.h"
#include "screen.h"
#include "Stage.h"
#include "Format.h"

extern Player* player;
extern Stage* stage;

void gameTickLoop(Map& gameMap, Snake& snake) {
    int dx = -1, dy = 0;
    nodelay(stdscr, TRUE);
    curs_set(0);

    auto lastTick = std::chrono::steady_clock::now();
    auto speedEndTime = std::chrono::steady_clock::now();
    auto startTime = std::chrono::steady_clock::now();
    int tickIntervalMs = 500;

    itemManager manager;
    Format format;

    char currentKey = 'w';
    std::string currentArrow = "↑";


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
        // 입력된 키 출력 (w/s/a/d 출력, 디버깅용)
        if (ch == 'w') {
            currentKey = 'w'; currentArrow = "↑";
        } else if (ch == 's') {
            currentKey = 's'; currentArrow = "↓";
        } else if (ch == 'a') {
            currentKey = 'a'; currentArrow = "←";
        } else if (ch == 'd') {
            currentKey = 'd'; currentArrow = "→";
        }


        if (elapsed >= tickIntervalMs) {

            lastTick = now;

            // 1. 아이템 처리
            manager.spawnItems(gameMap);
            manager.removeExpiredItems(gameMap);
            
            // 2. Snake 이동 실패 시 → 충돌이므로 실패
            if (!moveSnake(snake, gameMap, dx, dy, &manager, tickIntervalMs, speedEndTime)) {
                player->SetLengthScore(snake.length);
                player->SetTotalScore(snake.length);
                printStageResult(false);
                return;
            }

            // 3. Snake 길이 < 3이면 즉시 종료
            if (snake.length < 3) {
                player->SetLengthScore(snake.length);
                player->SetTotalScore(snake.length);
                printStageResult(false);
                return;
            }

            // 4. 속도 회복 처리
            if (tickIntervalMs < 500 && now >= speedEndTime) { //속도 조절, tickIntervalMs과 일치해야 함
                tickIntervalMs = 500;
            }

            // 5. 점수 계산
            player->SetLengthScore(snake.length);
            player->SetTotalScore(snake.length);

            // 6. 미션 달성 시 성공 처리
            if (!stage->clear && checkMissionComplete(player, stage)) {
                stage->clear = true;

                // 미션 클리어 화면 출력 + 점수 요약
                nodelay(stdscr, FALSE);  // 키 입력 대기 모드로 전환
                printStageResult(true);
                nodelay(stdscr, TRUE);   // 다시 논블로킹 모드로 복구

                return;  // 다음 스테이지로 이동
            }

            // 7. 타임아웃 체크
            float eTime = std::chrono::duration<float>(now - startTime).count();
            if (eTime >= 60.0f) {
                player->SetLengthScore(snake.length);
                player->SetTotalScore(snake.length);

                // 게임오버 화면 출력
                nodelay(stdscr, FALSE);
                printGameOverScreen(TIME_OUT);

                // 결과 요약 및 종료
                printStageResult(false);
                nodelay(stdscr, TRUE);
                return;
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

            // 점수판 출력
            eTime = std::chrono::duration<float>(now - startTime).count();
            format.Update(eTime);
            format.Render();

            // 입력된 키 출력
            move(0, 0);
            clrtoeol();
            printw("입력된 키: %c %s", currentKey, currentArrow.c_str());

            refresh();
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}


