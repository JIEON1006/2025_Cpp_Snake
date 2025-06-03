#include "map/map.h"
#include "start_screen.h"
#include "block.h"
#include "snakeManager.h"
#include "snake.h"
#include "gameManager.h"
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

    // snake 초기화 
    int x = gameMap.row / 2;
    int y = gameMap.col / 2;

    delete gameMap.mapArray[x][y];
    snakeHead* head = new snakeHead("Head", x, y);
    gameMap.mapArray[x][y] = head;
    gameMap.map[x][y] = SNAKE_HEAD;

    Snake snake;
    snake.head = head;
    snake.length = 3;
    snake.body.push_back({x + 1, y});
    snake.body.push_back({x + 2, y});

    // tick마다 방향키 입력받아 작동 
    gameTickLoop(gameMap, snake);

    endwin();
    return 0;
}
