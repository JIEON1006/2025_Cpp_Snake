#pragma once

class Map {
    
public:
    //void test(); // map 클래스 테스트용 출력 함수

    void map_draw(int startY, int startX);  // 화면에 맵을 출력
    void map_draw_test();                        // 테스트용 출력 함수

private:
    static const int height = 10; //map_draw() 테스트용 
    static const int width = 20; //map_draw() 테스트용 

    const char* mapData[height] = { //map_draw() 테스트용 
        "####################",
        "#..............#...#",
        "#.######.#######.#.#",
        "#.#....#.#.....#.#.#",
        "#.#.##.#.#.###.#.#.#",
        "#.#.#..#.#.#.#.#.#.#",
        "#.#.####.#.#.#.#.#.#",
        "#.#......#.#.#.#...#",
        "#.########.#.#.#####",
        "####################"
    };
};
