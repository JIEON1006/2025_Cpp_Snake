#pragma once

#include <iostream>
#include <string>
#include <ncurses.h>
using namespace std;

/*
0 : snake가 자유롭게 이동가능한 공백 블럭
1 : 그냥 벽 - gate 블럭으로 변환 가능
2 : 모서리 벽 - gate 블럭으로 변환 불가 
3 : snake의 머리        //2단계 구현 사항
4 : snake의 몸통        //2단계 구현 사항
5 : gate 블럭           //3단계 구현 사항
6 : plus 아이템         //4단계 구현 사항
7 : minus 아이템        //4단계 구현 사항
*/

// 과제 : 블럭 클래스를 작성, 특징에 맞는 전역 멤버 함수 설정
class Block{
    public:
        int type;         // 블럭의 타입
        int colorPair;    // 블럭 색상 쌍 번호
        int x, y;         // 블럭의 위치 좌표 
        char print(){
            return "■";
        }
};

// Block type을 상속받기
class blankBlock : public Block{
    public:
    type = 0;
}

class wallBlock : public Block{
    public:
    type = 1;
}

class NonGateWallBlock : public Block{
    public:
    type = 2;
}