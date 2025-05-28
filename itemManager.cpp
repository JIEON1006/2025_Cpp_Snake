#include <ctime>
#include <cstdlib>
#include <string>
#include "snake.h" //제작 예정
#include "item.h" // 제작 예정
#include "itemManager.h" // 제작 예정

// extern mapmanager *mapmanager <-mapmanager 제작 필요



itemManager::itemManager()
{
    getmaxyx(stdscr, maxheight, maxwidth);  // 콘솔 화면의 가로 세로 크기 측정
}

itemManager::~itemManager() 
{ 

}

void ItemManager::Render()
{

}


// 아이템 시간 초과 판단
bool isExceedTime(item item, float eTime)
{
    if (eTime - item.dropTime > 5) // 아이템은 3개까지, 5초간 존재
    {
        return true;
    }
    return false;
}


// 
void itemManager::DeleteCollisionData(int y, int x)
{
    int target;

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].position.x == x && data[i].position.y == y)
        {
            target = i;
        }
    }
    data.erase(data.begin() + target);
}

void itemManager::Update(float eTime)
{
    int *temp = new int[data.size()]; // 삭제 여부 표시용 배열

    // 일정 시간 후 새로운 아이템 생성(grow-fruit, minus-poison, speed, double)
    int randNum = rand() % 4;

    switch (randNum) {
        case 0:
            PositionItem("fruit", eTime);
            break;
        case 1:
            PositionItem("poison", eTime);
            break;
        case 2:
            PositionItem("speed", eTime); 
            break;
        case 3:
            PositionItem("double", eTime); 
            break;

        PushData();
        lastDroptime = eTime;

}

    // 삭제할 아이템 표시
    for (int i = 0; i < data.size(); i++)
        temp[i] = isExceedTime(data[i], eTime) ? 1 : 0;

    // 뒤에서부터 삭제 (앞에서 삭제하면 인덱스 꼬일 수 있음)
    for (int i = data.size() - 1; i >= 0; i--)
    {
        if (temp[i] == 1)
        {
            mapManager->PatchData(data[i].position.y, data[i].position.x, '0'); 
            data.erase(data.begin() + i); 
        }
    }

    delete[] temp;
    PushData(); // 다시 맵에 적용
}


// 아이템 생성
void itemManager::PositionItem(std::string check, float eTime)
{
    if (check == "fruit")
        data.push_back(Item("fruit", eTime));
    else if (check == "poison")
        data.push_back(Item("poison", eTime));
    else if (check == "speed")
        data.push_back(Item("speed", eTime));
    else if (check == "double")
        data.push_back(Item("double", eTime)); 
    
}

// 맵에 반영
void itemManager::PushData()
{
    for (intnn i = 0; i < data.size(); i++) // map size 확인필요
    {
        if (data[i].type == "fruit")
            mapManager->PatchData(data[i].position.y, data[i].position.x, '6');
        else if (data[i].type == "poison")
            mapManager->PatchData(data[i].position.y, data[i].position.x, '7');
        else if (data[i].type == "speed")
            mapManager->PatchData(data[i].position.y, data[i].position.x, '8');
        else if (data[i].type == "double")
            mapManager->PatchData(data[i].position.y, data[i].position.x, '9');
    }
}
