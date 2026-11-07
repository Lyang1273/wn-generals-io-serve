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
    FogMountain,
    Count
};

// 坐标
struct Point {
    int x = 0;
    int y = 0;

    Point(int x, int y): x(x), y(y) {}

    bool operator == (const Point &o) const {
        return x == o.x && y == o.y;
    }

    bool operator != (const Point &o) const {
        return !(*this == o);
    }

    Point operator + (const Point &o) const {
        return Point(x + o.x, y + o.y);
    }

    Point operator - (const Point &o) const {
        return Point(x - o.x, y - o.y);
    }
};

}