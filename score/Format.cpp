//출력 위치 조정 필요

#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Player.h"
#include "Stage.h"
#include "Format.h"

extern Player *player;
extern Stage *stage;

Format::Format()
{
    gameStartTime = -1;
    gameTime = -1;
    getmaxyx(stdscr, maxheight, maxwidth);
}
Format::~Format()
{
}

void Format::Update(float eTime)
{
    DrawTime(eTime);
}

void Format::Render()
{
    DrawScore();
    DrawMission();
}

void Format::DrawScore() {
    move(7, maxwidth / 5 * 4 + 4);
    printw("< S C O R E >");

    for (int i = 0; i < 26; i++) {
        move(8, maxwidth / 5 * 4 - 3 + i);
        addch('-');
    }

    move(10, maxwidth / 5 * 4 + 4);
    printw("B : %d", player->lengthScore);

    move(11, maxwidth / 5 * 4 + 4);
    printw("+ : %d", player->growScore);

    move(12, maxwidth / 5 * 4 + 4);
    printw("- : %d", player->poisonScore);

    move(13, maxwidth / 5 * 4 + 4);
    printw("G : %d", player->gateScore);

    move(14, maxwidth / 5 * 4 + 4);
    printw("Speed x2 : %d", player->speedScore);

    move(15, maxwidth / 5 * 4 + 4);
    printw("Length x2 : %d", player->doubleScore);

    for (int i = 0; i < 26; i++) {
        move(18, maxwidth / 5 * 4 - 3 + i);
        addch('-');
    }
}

/*
void Format::DrawScore()
{

    move(7, maxwidth / 5 * 4 + 4);
    printw("< S C O R E >");

    for (int i = 0; i < 26; i++)
    {
        move(8, maxwidth / 5 * 4 - 3 + i);
        addch('-');
    }

    int digit = 100, totalScore = player->totalScore;

    for (int i = 0; i < 3; i++)
    {
        int digitScore;
        std::string s = "00000";

        digitScore = totalScore / digit;
        totalScore %= digit;

        for (int j = 0; j < 5; j++)
        {
            move(11 + j, maxwidth / 5 * 4 - 2 + 4 + i * 6);
            printw("%s", score[digitScore][j]);
        }
        digit /= 10;
    }

    for (int i = 0; i < 26; i++)
    {
        move(18, maxwidth / 5 * 4 - 3 + i);
        addch('-');
    }
}
*/

void Format::DrawTime(float eTime)
{
    int digit = 10;

    if (gameStartTime == -1)
    {
        gameStartTime = eTime;
    }

    gameTime = eTime - gameStartTime;
    gameTime = eTime - gameStartTime; //
    digitTime = (int)(60 - gameTime); //
    if (digitTime < 0) digitTime = 0; //


    for (int j = 0; j < 5; j++)
    {
        move(1 + j, maxwidth / 5 * 4 - 2 + 2);
        printw("%s", score[0][j]);
    }

    for (int i = 0; i < 26; i++)
    {
        move(6, maxwidth / 5 * 4 - 3 + i);
        addch('-');
        move(0, maxwidth / 5 * 4 - 3 + i);
        addch('-');
    }

    move(2, maxwidth / 5 * 4 - 2 + 8);
    addch(char(219));

    move(4, maxwidth / 5 * 4 - 2 + 8);
    addch(char(219));

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            move(1 + j, maxwidth / 5 * 4 - 2 + 4 + (i + 1) * 6);
            printw("%s", score[digitTime / digit][j]);
        }
        digitTime = digitTime % digit;
        digit /= 10;
    }
}

char Format::Complete(int present, int goal)
{
    if (present >= goal)
        return 'V';
    else
        return ' ';
}

void Format::DrawMission()
{
    int *nowMission = stage->getNowMission();

    move(maxheight / 2, maxwidth / 5 * 4 + 1);
    printw("< M I S S I O N >");

    for (int i = 0; i < 26; i++)
    {
        move(maxheight / 2 + 1, maxwidth / 5 * 4 - 3 + i);
        addch('-');
    }

    move(22, maxwidth / 5 * 4 + 4);
    printw("Length : %d/%d (%c)", player->lengthScore, nowMission[0], Complete(player->lengthScore, nowMission[0]));

    move(24, maxwidth / 5 * 4 + 4);
    printw("Fruit : %d/%d (%c)", player->growScore, nowMission[1], Complete(player->growScore, nowMission[1]));

    move(26, maxwidth / 5 * 4 + 4);
    printw("Poison : %d/%d (%c)", player->poisonScore, nowMission[2], Complete(player->poisonScore, nowMission[2]));

    move(28, maxwidth / 5 * 4 + 4);
    printw("Gate : %d/%d (%c)", player->gateScore, nowMission[3], Complete(player->gateScore, nowMission[3]));

    move(30, maxwidth / 5 * 4 + 4);
    printw("Speed x2 : %d/%d (%c)", player->speedScore, nowMission[4], Complete(player->speedScore, nowMission[4]));

    move(32, maxwidth / 5 * 4 + 4);
    printw("Length x2 : %d/%d (%c)", player->doubleScore, nowMission[5], Complete(player->doubleScore, nowMission[5]));

    for (int i = 0; i < 26; i++)
    {
        move(34, maxwidth / 5 * 4 - 3 + i);
        addch('-');
    }
}