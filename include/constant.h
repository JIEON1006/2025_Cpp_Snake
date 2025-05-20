#pragma once

#include <iostream>
#include <string>
#include <ncurses.h>
using namespace std;

char mapping(int num){
    switch(num) {
        case 0: return '■';     // 0 : snake가 자유롭게 이동가능한 공백 블럭
        case 1: return '■';     // 1 : 그냥 벽
        case 2: return '■';     // 2 : 모서리 벽
        case 3: return '■';     // 3 : snake의 머리
        case 4: return '■';     // 4 : snake의 몸통
        case 5: return '■';     // 5 : gate 블럭
        case 6: return '■';     // 6 : plus 아이템
        case 7: return '■';     // 7 : minus 아이템 
        // ... 기타 블럭 추가 가능 
    }
}