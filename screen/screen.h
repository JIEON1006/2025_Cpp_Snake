#pragma once
#include <string>
#include <iostream>

void showStartScreen();
void printGameOverScreen(const std::string& cause);
void printStageResult(bool success);


#define LENGTH_ERR "몸 길이가 3 미만입니다"
#define WALL_ERR "벽에 부딪혔습니다"
#define BODY_ERR "반대 방향이 입력됐거나 바디에 부딪혔습니다"
#define TIME_OUT "시간이 만료되었습니다"