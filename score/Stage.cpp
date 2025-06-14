#include "Stage.h"
#include "map.h"
#include <ncurses.h>
#include <sstream>
#include <fstream>
#include <iostream>

// 생성자
Stage::Stage() {
    nowStage = 0;
    clear = false;
}

// 소멸자
Stage::~Stage() {}

// 게임 진행 중 로직 처리 (현재는 비어 있음)
void Stage::Update(float eTime) {
    // 미션 조건 확인 로직을 여기에 구현 가능
}

// 현재 스테이지 상태 출력 (디버깅용)
void Stage::Render() {
    mvprintw(0, 0, "Current Stage: %d", nowStage);
    if (clear) {
        mvprintw(1, 0, "Stage Clear!");
    } else {
        mvprintw(1, 0, "Stage In Progress...");
    }
}



