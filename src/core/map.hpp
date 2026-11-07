/*
    定义游戏的地图
*/
#pragma once
#include "type.hpp"
#include <vector>

namespace gen::core {

inline constexpr int NEUTRAL = -1; // 中立单位所有者为 -1 

struct Tile {
    Terrain terrain = Terrain::Blank;
    int owner = NEUTRAL;
    int unit = 0;

    Tile() = default;

    Tile(Terrain terrain, int owner, int unit): terrain(terrain), owner(owner), unit(unit) {}

    bool isNeutral() const {
        return owner == NEUTRAL;
    }
};

// 地图坐标 0-index
class GameMap {
private:
    std::vector<Tile> tiles; // 存储地图的二维数组
public:
    int R, C;

    GameMap(int R, int C);

    Tile& at(int x, int y); //返回该格的引用

    Tile& at(const Point &p);

    Tile get(int x, int y) const; //返回该格的值

    Tile get(const Point &p) const;

    void set(int x, int y, const Tile &tile); //设置该格的值

    void set(const Point &p, const Tile &tile);

    bool isInside(int x, int y) const; // 判断坐标是否在地图内

    bool isInside(const Point &p) const;

    Tile* operator[](int x);
};

}