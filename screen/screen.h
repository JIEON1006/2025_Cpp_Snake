#pragma once
#include <iostream>

void showStartScreen();
void printGameOverScreen(const std::string cause);

#define LENGTH_UNDER_3 "몸 길이가 3 미만입니다"
#define WALL "벽에 부딪혔습니다"
#define BODY "반대 방향이 입력됐거나 바디에 부딪혔습니다"