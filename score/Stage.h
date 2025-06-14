#pragma once

#include "IObject.h"
#include "map.h"  // Map 클래스 사용을 위해 필요

class Stage : public IObject {
public:
    int nowStage;       // 현재 스테이지 번호
    bool clear;         // 클리어 여부

    // 미션 배열 (뱀 길이, grow 아이템, poison 아이템, gate 아이템, speed 아이템, double 아이템)
    int mission[3][6] = {
        {6, 1, 1, 1, 1, 1},
        {6, 2, 2, 2, 1, 1},
        {6, 2, 3, 3, 2, 2},
    };

    Stage();            // 생성자
    ~Stage();           // 소멸자

    int getNowStage() { return nowStage; }
    int* getNowMission() { return mission[nowStage]; }
    void setNowStage(int nowStage) { this->nowStage = nowStage; }

    void Update(float eTime) override;  // IObject 상속
    void Render() override;

};
