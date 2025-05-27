#pragma once

#include <iostream>
#include <string>
#include <ncurses.h>
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

    virtual const char* print() const = 0;  // 포인터 X
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
