#include "map.h"
#include <iostream>

void Map::test() {
    std::cout << "맵 출력 테스트 성공!" << std::endl;
}

// 숫자 -> 문자 변환 매핑 함수
void mapping(int num=0, int x=0, int y=0){
    switch (num)
    {
    case 0:
        /* 배열 좌표(x, y)에 blankBlock 저장 */
        break;
    
    case 1:
        /* 배열 좌표(x, y)에 wallBlock 저장 */
        break;

    case 2:
        /* 배열 좌표(x, y)에 NonGateWallBlock 저장 */
        break;
    }
}