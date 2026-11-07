/*
    定义游戏的类型
*/
#pragma once
#include <cstdint>

namespace gen::core {

// 地形
enum class Terrain : uint8_t {
    Blank,
    Swamp,
    Mountain,
    Capital,
    City,
    Count
};

// 玩家可以看见的地形
enum class VisibleTerrain : uint8_t {
    Blank,
    Swamp,
    Mountain,
    Capital,
    City,
    FogBlank,
    FogMoutain,
    Count
};

// 坐标
struct Point {
    int x;
    int y;

    Point(int x, int y): x(x), y(y) {}

    bool operator == (const Point &o) const {
        return x == o.x && y == o.y;
    }

    bool operator != (const Point &o) const {
        return !(*this == o);
    }
};

}