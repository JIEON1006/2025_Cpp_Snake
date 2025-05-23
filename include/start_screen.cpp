#include <ncurses.h>
#include <unistd.h>
#include "start_screen.h"

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
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
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
