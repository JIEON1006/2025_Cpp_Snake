#include "map/map.h"
#include "start_screen.h"
#include "block.h"
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

    int ch;
    int x = gameMap.row, y = gameMap.col;

    delete gameMap.mapArray[x/2][y/2];
    snakeHead* head = new snakeHead("head", x/2, y/2);
    gameMap.mapArray[x/2][y/2] = head;

    deque<pair<int, int>> tails;
    int tailLength = 3;

    tails.push_back({head->x + 1, head->y});
    tails.push_back({head->x + 2, head->y});

    while (ch = getch()) {
        int newX = (head->x);
        int newY = (head->y);

        switch (ch) {
            case 'w': newX--; break;
            case 's': newX++; break;
            case 'a': newY--; break;
            case 'd': newY++; break;
            default: continue;
        }

        tails.push_front({head->x, head->y});
        if ((int)tails.size() > tailLength) {
            pair<int, int> tailEnd = tails.back();
            tails.pop_back();

            delete gameMap.mapArray[tailEnd.first][tailEnd.second];
            gameMap.mapArray[tailEnd.first][tailEnd.second] = new blankBlock("Blank");
        }
        
        delete gameMap.mapArray[head->x][head->y];
        gameMap.mapArray[head->x][head->y] = new snakeTail("Tail", head->x, head->y);
        
        (head->x) = newX;
        (head->y) = newY;

        if (dynamic_cast<wallBlock*>(gameMap.mapArray[newX][newY]) || dynamic_cast<NonGateWallBlock*>(gameMap.mapArray[newX][newY]) || dynamic_cast<snakeTail*>(gameMap.mapArray[newX][newY]))
            {
            mvprintw(0, 0, "Game Over!");    // test
            refresh();
            break;                           
            }   
        else{
            delete gameMap.mapArray[newX][newY];
            head = new snakeHead("Head", newX, newY);
            gameMap.mapArray[newX][newY] = head;
 

            x = newX; y = newY; 
            }

        clear();
        for (int i = 0; i < gameMap.row; ++i)
            for (int j = 0; j < gameMap.col; ++j)
                gameMap.mapArray[i][j]->print();
        refresh();
    }

    endwin();
    return 0;
}
