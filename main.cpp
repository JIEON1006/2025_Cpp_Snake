#include <ncurses.h>
#include "map.h"
#include "include/start_screen.h"
#include "include/block.h"
#include <locale.h>

int main() {
    // 1. 유니코드 특수 문자 출력을 위한 로케일 설정
    setlocale(LC_ALL, "");

    // 2. ncurses 초기화
    initscr();
    noecho();           // 사용자 입력을 화면에 표시하지 않음
    cbreak();           // 키를 누르면 바로 프로그램이 반응
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
    gameMap.printMap();        // 블록 문자 출력
    getch();                   // 사용자 키 입력 대기

    gameMap.printColoredMap(); // 색상 적용된 출력
    getch();

    // + 게임 실행 코드 
    int ch;
    int x = gameMap.row, y = gameMap.col;

    // 머리와 꼬리 위치 초기화 
    delete gameMap[x/2][y/2];
    gameMap[x/2][y/2] = new snakeHead("head", x/2, y/2);
    deque<pair<int, int>> tails;
    int tailLength = 3;

    // 꼬리 초기 길이 2개, 머리 뒤에 쭉 이어짐
    tails.push_back(snakeTail(head.x + 1, head.y));
    tails.push_back(snakeTail(head.x + 2, head.y));

    while (ch = getch()) {
        int newX = head.x;
        int newY = head.y;
        
         // 방향키 조작
        switch (ch) {
            case 'w': newX--; break;
            case 's': newX++; break;
            case 'a': newY--; break;
            case 'd': newY++; break;
            default: continue;
        }

        tails.push_front(snakeTail(head.x, head.y));    // 머리의 현재 위치를 꼬리 앞에 추가
        if ((int)tails.size() > tailLength) {
            pair<int, int> tailEnd = tails.back();
            tails.pop_back();

            // 꼬리 자취 지우고 blankBlock 할당
            delete gameMap[tailEnd.first][tailEnd.second];
            gameMap[tailEnd.first][tailEnd.second] = new blankBlock("Blank");
        }
        // 이전 머리 자리는 꼬리로 바꾸기
        delete gameMap[head.x][head.y];
        gameMap[head.x][head.y] = new snakeTail("Tail");
        
        head.x = newX;          // 머리 이동
        head.y = newY;

        if (dynamic_cast<wallBlock*>(gameMap[newX][newY]) || dynamic_cast<NonGateWallBlock*>(gameMap[newX][newY]) || dynamic_cast<snakeTail*>(gameMap[newX][newY]))
            {
            mvprintw(0, 0, "Game Over!");    // Game over 문구 출력 (시험용)
            refresh();
            break;                           // While 루프 종료
            }   
        else{
            delete gameMap[newX][newY];      // 이동 위치 제거
            gameMap[newX][newY] = new snakeHead("Head"); // 새 위치에 snakeHead 배치

            x = newX; y = newY; 
            }

        // 화면 출력
        clear();
        for (int i = 0; i < gameMap.row; ++i)
            for (int j = 0; j < gameMap.col; ++j)
                gameMap[i][j]->print();
        refresh();
    }

    // 6. 종료
    endwin();
    return 0;
}
