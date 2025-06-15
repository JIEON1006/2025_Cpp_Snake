#pragma once

#include <iostream>
#include "ncurses.h"
#include <string>
#include <vector>
#include <deque>
using namespace std;

#define BLANK   " "
#define FILL_BLOCK    "■"
#define FILL_DIAMOND  "◆"
#define TAIL          "○"
#define HEAD          "●"
#define GATE_PRINT    "×"
#define GROWTH "＋"
#define POISION "－"
#define SPEED_DOUBLE "⇈"
#define LENGTH_DOUBLE "★"

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
        return BLANK;
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

class snakeHead : public Block {
public:
    int x, y;
    snakeHead(const string& name_, int x, int y) : x(x), y(y) {
        this->type = 3;
        this->name = name_;
    }
    const char* print() const override {
        return HEAD;
    }
};

class snakeTail : public Block {
public:
    int x, y;
    snakeTail(const string& name_, int x, int y) : x(x), y(y) {
        this->type = 4;
        this->name = name_;
    }
    const char* print() const override {
        return TAIL;
    }
};

class gateBlock : public Block {
public:
    gateBlock(const std::string& name_) {
        this->type = 5;
        this->name = name_;
    }

    const char* print() const override {
        return GATE_PRINT;  
    }
};

class itemBlock : public Block {
public:
    std::string itemType; // "fruit", "poison", "speed", "double"

    itemBlock(const string& name_, const string& itemType_) {
        this->type = 6;  // 아이템은 type 6 이상
        this->name = name_;
        this->itemType = itemType_;
    }

    const char* print() const override {
        if (itemType == "fruit") return GROWTH;
        else if (itemType == "poison") return POISION;
        else if (itemType == "speed") return SPEED_DOUBLE;
        else if (itemType == "double") return LENGTH_DOUBLE;
        return "?";
    }
};

// 좌표를 입력받아 해당 좌표의 Block 출력
void printBlockAt(int x, int y, const std::vector<std::vector<Block*>>& mapArray);

// 좌표와 색깔을 입력받아 해당 좌표의 Block 출력
void printColoredBlock(int x, int y, const std::vector<std::vector<Block*>>& mapArray,int colorPair);