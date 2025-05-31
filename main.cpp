#include "map/map.h"
#include "start_screen.h"
#include "block.h"
#include "snake_manager.h"
#include <locale.h>
#include <deque>
#include <utility>


int main() {

    setlocale(LC_ALL, "");

    initscr();
    noecho();           
    cbreak();           
    curs_set(0);        
    start_color();      
    use_default_colors(); 

    init_pair(1, COLOR_WHITE, -1);  
    init_pair(2, COLOR_GREEN, -1);  
    init_pair(3, COLOR_RED, -1);    
    init_pair(4, COLOR_BLUE, -1);   
    init_pair(5, COLOR_CYAN, -1);   
    keypad(stdscr, TRUE);           

    
    showStartScreen();
    clear();
    refresh();

    Map gameMap;               
    gameMap.printMap();        
    getch();                   

    gameMap.printColoredMap(); 
    getch();

    Snake snake;
    initSnake(snake, gameMap);

    int ch;
    while ((ch = getch())) {
        int dx = 0, dy = 0;
        switch (ch) {
            case 'w': dx = -1; break;
            case 's': dx = 1;  break;
            case 'a': dy = -1; break;
            case 'd': dy = 1;  break;
            default: continue;
        }

        if (!moveSnake(snake, gameMap, dx, dy)) {
            mvprintw(0, 0, "Game Over!");
            refresh();
            break;
        }

        renderMap(gameMap);
    }

    endwin();
    return 0;
}
