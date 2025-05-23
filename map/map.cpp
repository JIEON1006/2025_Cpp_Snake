#include "map.h"
#include <iostream>
#include <ncurses.h>

/*
void Map::test() {
    std::cout << "맵 출력 테스트 성공!" << std::endl;
}
*/


void Map::map_draw(int startY, int startX) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            mvaddch(startY + y, startX + x, mapData[y][x]);
        }
    }
}

void Map::map_draw_test() {
    int startY = (LINES - height) / 2;
    int startX = (COLS - width) / 2;
    map_draw(startY, startX);
    refresh();
}