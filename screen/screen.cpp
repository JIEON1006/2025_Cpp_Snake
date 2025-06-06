
#include <unistd.h>
#include <ncurses.h>
#include "screen.h"
#include <iostream>

void drawAnimatedBorder(int delay_us = 1500) {
    int height, width;
    getmaxyx(stdscr, height, width);

    attron(A_BOLD);
    for (int x = 0; x < width; ++x) {
        mvaddch(0, x, '-'); refresh(); usleep(delay_us);
    }
    for (int y = 1; y < height; ++y) {
        mvaddch(y, width - 1, '|'); refresh(); usleep(delay_us);
    }
    for (int x = width - 2; x >= 0; --x) {
        mvaddch(height - 1, x, '-'); refresh(); usleep(delay_us);
    }
    for (int y = height - 2; y > 0; --y) {
        mvaddch(y, 0, '|'); refresh(); usleep(delay_us);
    }

    // 코너
    mvaddch(0, 0, '+');
    mvaddch(0, width - 1, '+');
    mvaddch(height - 1, 0, '+');
    mvaddch(height - 1, width - 1, '+');

    attroff(A_BOLD);
}

void showStartScreen() {
    clear();
    int height, width;
    getmaxyx(stdscr, height, width);

    start_color();
    init_pair(1, COLOR_GREEN, -1);
    attron(COLOR_PAIR(1));

    drawAnimatedBorder(1500);

    const char* ascii[] = {
        "                               __                 ",
        "                              /  |                ",
        "  _______  _______    ______  $$ |   __   ______  ",
        " /       |/       \\  /      \\ $$ |  /  | /      \\ ",
        "/$$$$$$$/ $$$$$$$  | $$$$$$  |$$ |_/$$/ /$$$$$$  |",
        "$$      \\ $$ |  $$ | /    $$ |$$   $$<  $$    $$ |",
        " $$$$$$  |$$ |  $$ |/$$$$$$$ |$$$$$$  \\ $$$$$$$$/ ",
        "/     $$/ $$ |  $$ |$$    $$ |$$ | $$  |$$       |",
        "$$$$$$$/  $$/   $$/  $$$$$$$/ $$/   $$/  $$$$$$$/ "
    };

    int startY = height / 2 - 10;
    int startX = (width - 50) / 2;

    for (int i = 0; i < 9; ++i)
        mvprintw(startY + i, startX, "%s", ascii[i]);

    attroff(COLOR_PAIR(1));

    const char* msg = "Press Enter to Start";
    int msgX = (width - 25) / 2;
    mvprintw(startY + 11, msgX, "%s", msg);
    refresh();

    nodelay(stdscr, TRUE);  // 비차단 입력
    int ch = -1;
    int dotCount = 0;

    while (true) {
        ch = getch();
        if (ch == '\n' || ch == KEY_ENTER || ch == 10 || ch == 13) break;

        // 점 개수 업데이트 및 출력
        for (int i = 0; i < 3; ++i) {
            if (i < dotCount)
                mvaddch(startY + 11, msgX + 21 + i, '.');
            else
                mvaddch(startY + 11, msgX + 21 + i, ' ');
        }
        refresh();

        dotCount = (dotCount + 1) % 4;  // 0,1,2,3 반복
        usleep(300000);  // 0.3초
    }

    nodelay(stdscr, FALSE);  // 원상 복구
}

void printGameOverScreen(const std::string& cause) {
    int width = 55;  // 박스 너비를 넉넉하게 확보
    int height = 9;
    int startY = (LINES - height) / 2;
    int startX = (COLS - width) / 2;

    attron(A_BOLD);
    attron(COLOR_PAIR(3));

    // 상단 박스 테두리
    mvprintw(startY, startX,       "╔═════════════════════════════════════════════════════════════╗");
    mvprintw(startY + 1, startX,   "║                                                             ║");
    mvprintw(startY + 2, startX,   "║                     █▀▀ ▄▀█ █▀▄▀█ █▀▀                       ║");
    mvprintw(startY + 3, startX,   "║                     █▄▄ █▀█ █░▀░█ █▄▄                       ║");
    mvprintw(startY + 4, startX,   "║                                                             ║");

    // Reason 메시지 중앙 정렬
    std::string centeredCause = "Reason: " + cause;
    int causeX = startX + 1 + (width - 2 - centeredCause.length()) / 2+9;
    mvprintw(startY + 5, startX,   "║                                                             ║");
    mvprintw(startY + 5, causeX, "%s", centeredCause.c_str());

    // Press any key 메시지 중앙 정렬
    std::string exitMsg = "Press any key to exit...";
    int exitX = startX + 1 + (width - 2 - exitMsg.length()) / 2+5;
    mvprintw(startY + 6, startX,   "║                                                             ║");
    mvprintw(startY + 6, exitX, "%s", exitMsg.c_str());

    // 하단 박스 테두리
    mvprintw(startY + 7, startX,   "║                                                             ║");
    mvprintw(startY + 8, startX,   "╚═════════════════════════════════════════════════════════════╝");

    attroff(COLOR_PAIR(3));
    attroff(A_BOLD);

    refresh();
    nodelay(stdscr, FALSE);
    getch();
}
