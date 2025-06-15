#include "itemManager.h"
#include "Player.h" 
#include <random>
#include <algorithm>

extern Player* player; 


bool isExceedTime(const Item& item, std::chrono::steady_clock::time_point now) {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - item.spawnTime).count();
    return duration > 5;
}



void itemManager::DeleteCollisionData(int y, int x, Map& gameMap) {
    // 1. map 및 mapArray에서 아이템 제거
    delete gameMap.mapArray[y][x];
    gameMap.mapArray[y][x] = new blankBlock("blank");
    gameMap.map[y][x] = EMPTY;

    // 2. 내부 데이터에서도 제거
    auto it = std::find_if(data.begin(), data.end(),
                           [&](const Item& item) { return item.y == y && item.x == x; });

    if (it != data.end()) {
        data.erase(it);
    }
}


void itemManager::PositionItem(int x, int y, std::string type, std::chrono::steady_clock::time_point time) {
    data.push_back(Item(x, y, type, time));
}


void itemManager::PushData(Map& gameMap) {
    for (const auto& item : data) {
        int y = item.y;
        int x = item.x;

        // 1. map 값 설정
        if (item.type == "fruit")
            gameMap.map[x][y] = GROWTH_ITEM;
        else if (item.type == "poison")
            gameMap.map[x][y] = MINUS_ITEM;
        else if (item.type == "speed")
            gameMap.map[x][y] = DOUBLE_SPEED;
        else if (item.type == "double")
            gameMap.map[x][y] = DOUBLE_LENGTH;

        // 2. mapArray 값 설정 (기존 블록 제거 후 새로운 아이템 블록 생성)
        delete gameMap.mapArray[x][y];
        gameMap.mapArray[x][y] = new itemBlock("item", item.type);
    }
}


// 1. 아이템 생성
void itemManager::spawnItems(Map& gameMap) {
    if (data.size() >= static_cast<size_t>(MAX_ITEMS)) return;

    std::vector<std::pair<int, int>> candidates;
    for (int i = 0; i < gameMap.row; ++i) {
        for (int j = 0; j < gameMap.col; ++j) {
            if (gameMap.map[i][j] != EMPTY) continue;

            Block* block = gameMap.mapArray[i][j];
            if (dynamic_cast<snakeHead*>(block) || dynamic_cast<snakeTail*>(block)) continue;

            candidates.emplace_back(i, j);
        }
    }

    if (candidates.empty()) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(candidates.begin(), candidates.end(), gen);
    auto [x, y] = candidates.front();  

    std::vector<std::string> itemTypes = {"fruit", "poison", "speed", "double"};
    std::uniform_int_distribution<> dist(0, itemTypes.size() - 1);
    std::string type = itemTypes[dist(gen)];

    // vector에 저장만 함 
    auto now = std::chrono::steady_clock::now();
    PositionItem(x, y, type, now);

    PushData(gameMap);  // 맵에 반영
}



// 2. 아이템 제거
void itemManager::removeExpiredItems(Map& gameMap) {
    auto now = std::chrono::steady_clock::now();
    std::vector<Item> updated;

    for (auto& item : data) {
        if (!isExceedTime(item, now)) {
            updated.push_back(item);
        } else {
            delete gameMap.mapArray[item.x][item.y];
            gameMap.mapArray[item.x][item.y] = new blankBlock("blank");
            gameMap.map[item.x][item.y] = EMPTY;
        }
    }

    data = updated;
}

// 3. Snake와 충돌 검사
void itemManager::applyItemEffect(Snake& snake, Map& gameMap, int x, int y,
                                  int& snakeIntervalMs,
                                  std::chrono::steady_clock::time_point& speedEndTime)
{
    auto it = std::find_if(data.begin(), data.end(),
                           [&](const Item& item) { return item.x == x && item.y == y; });

    if (it != data.end()) {
        const std::string& type = it->type;

        if (type == "fruit") {
            snake.length++;
            player->growScore++;
        }
        else if (type == "poison") {
            snake.length--;
            player->poisonScore++;
        }
        else if (type == "speed") {
            snakeIntervalMs = 250; //250으로 줄이기?
            speedEndTime = std::chrono::steady_clock::now() + std::chrono::seconds(5);
            player->speedScore++;
        }
        else if (type == "double") {
            snake.length *= 2;
            player->doubleScore++;
        }

        // 공통적으로 처리
        player->SetLengthScore(snake.length);
        player->SetTotalScore(snake.length);  // 총점은 현재 뱀 길이로 정의됨

        // 아이템 제거
        DeleteCollisionData(y, x, gameMap);

    }
}
