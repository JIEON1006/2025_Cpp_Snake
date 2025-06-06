#pragma once
#include <string>
#include <chrono>

struct Item {
    int x;
    int y;
    std::string type;
    std::chrono::steady_clock::time_point spawnTime;

    Item() = default;  // 기본 생성자

    Item(int x, int y, const std::string& type, std::chrono::steady_clock::time_point time)
        : x(x), y(y), type(type), spawnTime(time) {}
};