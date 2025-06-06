#include "map.h"
#include <random>
#include <algorithm>

void placeGates(Map& gameMap);

std::pair<int, int> findExitPosition(std::pair<int, int> gatePos, const Map& gameMap, int inDx, int inDy);
