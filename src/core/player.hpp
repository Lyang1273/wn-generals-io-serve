/*
    玩家和小队
*/

#pragma once
#include "type.hpp"
#include <vector>
#include <memory>
#include <queue>

namespace gen::core {

struct Player {
    int playerID = 0; // 玩家ID
    int teamID = 0; // 队伍ID
    bool alive = true; // 存活状态
    int units = 0; // 兵力数量
    int tiles = 0; // 占领的地块数量

    Player(int playerID, int teamID): playerID(playerID), teamID(teamID) {}
};

struct Team {
    int teamID = 0;
    int alivePlayers = 0;
    bool alive = true; // 队伍存活状态
    int units = 0; // 队伍总兵力数量
    int tiles = 0; // 队伍总占领地块数量
    std::vector<int> players; // 队伍中的玩家 ID

    Team(int teamID): teamID(teamID) {}
};

class PlayerRegistry {
private:
    int playerCount = 0; // 玩家数量

    int teamCount = 0; // 队伍数量

    bool isRegisteredMoveQueue = true; // 是否已经注册移动队列

    std::vector<std::unique_ptr<Player>> players; // 全局玩家列表

    std::vector<std::unique_ptr<Team>> teams; // 全局队伍列表

    std::queue<Player*> moveQueue; // 移动优先级队列
public:
    PlayerRegistry() = default;

    void registerPlayer(int playerID, int teamID); // 注册一个玩家 不构造 moveQueue

    void registerMoveQueue(); // 构造移动优先级队列

    const std::queue<Player*>& getMoveQueue() const {
        return moveQueue;
    }

    void nextMoveQueue(); // 移动队列向后推迟 优先级最高的玩家变优先级最低

    bool isSameTeam(int playerID1, int playerID2) const; // 判断两个玩家是否属于同一队伍

    Player* atPlayer(int playerID) const; // 获得该玩家

    Team* atTeam(int teamID) const; // 获得该小队

    void updatePlayerState(int playerID, int deltaUnits, int deltaTiles); // 更新玩家状态 加上或减去 units tiles 用正负号区分

    void markNotAlive(int playerID); // 标记不存话 同时清空玩家数据
};

}