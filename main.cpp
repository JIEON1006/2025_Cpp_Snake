#include "map/map.h"
#include "start_screen.h"
#include "block.h"
#include "snakeManager.h"
#include "snake.h"
#include "gameManager.h"
#include "gate.h"
#include <locale.h>
#include <deque>
#include <utility>


int main() {

      // 1. 유니코드 특수 문자 출력을 위한 로케일 설정
    setlocale(LC_ALL, "");

    // 2. ncurses 초기화
    initscr();
    noecho();           // 사용자 입력을 화면에 표시하지 않음
    curs_set(0);        // 커서 숨기기
    start_color();      // 컬러 사용 가능하게 설정
    use_default_colors();  // 배경색 -1 가능 (터미널 기본 배경색)

    // 3. 컬러쌍 정의 (앞: 글자색, 뒤: 배경색)
    init_pair(1, COLOR_WHITE, -1);  // 기본
    init_pair(2, COLOR_GREEN, -1);  // snake body
    init_pair(3, COLOR_RED, -1);    // wall
    init_pair(4, COLOR_BLUE, -1);   // immune wall
    init_pair(5, COLOR_CYAN, -1);   // gate
    keypad(stdscr, TRUE);           // 방향키 입력 허용

    // 4. 시작 화면 출력
    showStartScreen();
    clear();
    refresh();

    // 5. 맵 객체 생성 및 출력
    Map gameMap;               // map.txt로부터 정수 map 로딩 및 Block 배열 생성
    placeGates(gameMap);       //  게이트 2개를 맵에 배치 (벽에서 선택)

    Snake snake;
    initSnake(snake, gameMap);

    //gameMap.printMap();        // 블록 문자 출력
    //getch();

    // snake 초기화 
    int x = gameMap.row / 2;
    int y = gameMap.col / 2;

    delete gameMap.mapArray[x][y];
    snakeHead* head = new snakeHead("Head", x, y);
    gameMap.mapArray[x][y] = head;
    gameMap.map[x][y] = SNAKE_HEAD;

    //Snake snake;
    //snake.head = head;
    //snake.length = 3;
    //snake.body.push_back({x + 1, y});
    //snake.body.push_back({x + 2, y});

    // tick마다 방향키 입력받아 작동 
    gameTickLoop(gameMap, snake);

    endwin();
    return 0;
}
