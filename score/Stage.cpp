#include "Stage.h"
#include "map.h"
#include <ncurses.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Player.h"

extern Player* player;


// 생성자
Stage::Stage() {
    nowStage = 0;
    clear = false;
}

// 소멸자
Stage::~Stage() {}

// 게임 진행 중 로직 처리
void Stage::Update(float eTime) {
    if (!clear && checkMissionComplete(player, this)) {
        clear = true;
    }
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

bool checkMissionComplete(Player* player, Stage* stage) {
    int* mission = stage->getNowMission();

    return player->lengthScore >= mission[0] &&
           player->growScore   >= mission[1] &&
           player->poisonScore >= mission[2] &&
           player->gateScore   >= mission[3] &&
           player->speedScore  >= mission[4] &&
           player->doubleScore >= mission[5];
}

