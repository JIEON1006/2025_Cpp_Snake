#include <ncurses.h>
#include "map/map.h"
#include "start_screen.h"

int main() {
    initscr(); noecho(); curs_set(0); cbreak(); keypad(stdscr, TRUE);

    showStartScreen();  // 초기화면

    Map gameMap;
    int startY = (LINES - 10) / 2;
    int startX = (COLS - 20) / 2;
    clear();
    gameMap.map_draw(startY, startX);  // 맵 출력
    refresh();

    getch();  // 종료 대기
    endwin();
    return 0;
}
