#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <ncursesw/ncurses.h>  // 꼭 ncursesw 사용해야 mvaddwstr 사용 가능!

using namespace std;

#define BLANK_BLOCK   "□"
#define FILL_BLOCK    "■"
#define FILL_DIAMOND  "◆"



class Block {
public:
    int type;
    int colorPair;
    int x, y;
    string name;

    Block() : type(0), colorPair(0), x(0), y(0), name("") {}
    virtual ~Block() {}

    virtual const char* print() const = 0;
};

class blankBlock : public Block {
public:
    blankBlock(const string& name_) {
        this->type = 0;
        this->name = name_;
    }

    const char* print() const override {
        return BLANK_BLOCK;
    }
};

class wallBlock : public Block {
public:
    wallBlock(const string& name_) {
        this->type = 1;
        this->name = name_;
    }

    const char* print() const override {
        return FILL_BLOCK;
    }
};

class NonGateWallBlock : public Block {
public:
    NonGateWallBlock(const string& name_) {
        this->type = 2;
        this->name = name_;
    }

    const char* print() const override {
        return FILL_DIAMOND;
    }
};

// 좌표를 입력받아 해당 좌표의 Block 출력
void printBlockAt(int x, int y, const std::vector<std::vector<Block*>>& mapArray);

// 좌표와 색깔을 입력받아 해당 좌표의 Block 출력
void printColoredBlock(int x, int y, const std::vector<std::vector<Block*>>& mapArray,int colorPair);