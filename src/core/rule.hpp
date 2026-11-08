/*
    处理游戏操作和规则
*/
#pragma once
#include "map.hpp"
#include "player.hpp"
#include <generals/direction.h>

namespace gen::core {

struct MoveOperation {
    int playerID = 0;
    Point source;
    int d = 0; // 表示方向 方向定义见 include/generals/direction.h
    bool half; // 是否挪动一半兵力

    MoveOperation(int playerID, Point source, int d, bool half): playerID(playerID), source(source), d(d), half(half) {}
};

class Rule {
public:
    static bool isValidMove(const GameMap &map, const MoveOperation &op); // 判断移动是否合法

    static void applyMove(GameMap &map, PlayerRegistry &playerRegistry, const MoveOperation &op); // 执行移动操作

    static void occupy(GameMap &map, PlayerRegistry &playerRegistry, Tile &destTile, int sourceID, int moveUnits); // 占领某个地块

    static void beatPlayer(GameMap &map, PlayerRegistry &playerRegistry, int sourceID, int defeatenID); // 击败玩家

    static void 
};

// 将方向转换为坐标偏移量 
inline Point directionToPoint(int d) {
    return Point(directions[d][0], directions[d][1]);
}

// 计算移动后的位置
inline Point calcDestination(const Point &source, int d) {
    return source + directionToPoint(d);
}

}