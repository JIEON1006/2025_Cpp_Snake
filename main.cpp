#include "map/map.h"
#include "screen.h"
#include "block.h"
#include "snakeManager.h"
#include "snake.h"
#include "gameManager.h"
#include "gate.h"
#include "Player.h"
#include "Stage.h"
#include "Format.h"

#include <locale.h>
#include <deque>
#include <utility>

Player* player = nullptr;
Stage* stage = nullptr;

int main() {
    // 1. 유니코드 특수 문자 출력을 위한 로케일 설정
    setlocale(LC_ALL, "");

    // 2. ncurses 초기화
    initscr();
    noecho();
    curs_set(0);
    start_color();
    use_default_colors();

    init_pair(1, COLOR_WHITE, -1);  // 기본
    init_pair(2, COLOR_GREEN, -1);  // snake body
    init_pair(3, COLOR_RED, -1);    // wall
    init_pair(4, COLOR_BLUE, -1);   // immune wall
    init_pair(5, COLOR_CYAN, -1);   // gate

    keypad(stdscr, TRUE);

    // 3. 전역 객체 초기화
    player = new Player();
    stage = new Stage();

    // 4. 시작 화면 출력
    showStartScreen();
    clear();
    refresh();

    // 5. 총 3 스테이지 반복
    for (int i = 0; i < 4; ++i) {
        stage->setNowStage(i);              // 현재 스테이지 설정
        
        gateInitialized = false; 
        
        Map gameMap(i);                     // 스테이지별 맵 로딩
        placeGates(gameMap);                // 게이트 배치

        Snake snake;
        initSnake(snake, gameMap);

        int x = gameMap.row / 2;
        int y = gameMap.col / 2;

        delete gameMap.mapArray[x][y];      // 기존 블록 제거
        snakeHead* head = new snakeHead("Head", x, y);
        gameMap.mapArray[x][y] = head;
        gameMap.map[x][y] = SNAKE_HEAD;

        gameTickLoop(gameMap, snake);       // 게임 루프 실행

        clear(); // 다음 스테이지 전에 화면 정리
    }

    // 6. 종료 처리
    endwin();

    // 7. 동적 메모리 해제
    delete player;
    delete stage;

    return 0;
}
