#include "block.h"
#include <vector>

using namespace std;

void printBlockAt(int x, int y, const std::vector<std::vector<Block*>>& mapArray) {
    int row = mapArray.size();
    int col = (row > 0) ? mapArray[0].size() : 0;

    int startY = (LINES - row) / 2;
    int startX = (COLS - col * 2) / 2;

    if (x >= 0 && x < row && y >= 0 && y < col && mapArray[x][y]) {
        mvaddstr(startY + x, startX + y * 2, mapArray[x][y]->print());
    }
}

void printColoredBlock(int x, int y, const std::vector<std::vector<Block*>>& mapArray, int colorPair) {
    int row = mapArray.size();
    int col = (row > 0) ? mapArray[0].size() : 0;

    int startY = (LINES - row) / 2;
    int startX = (COLS - col * 2) / 2;

    if (x >= 0 && x < row && y >= 0 && y < col && mapArray[x][y]) {
        attron(COLOR_PAIR(colorPair));
        mvaddstr(startY + x, startX + y * 2, mapArray[x][y]->print());
        attroff(COLOR_PAIR(colorPair));
    }
}