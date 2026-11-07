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
    std::shared_ptr<Team> team; // 玩家所属队伍
    bool alive = true; // 存活状态
    int units = 0; // 兵力数量
    int tiles = 0; // 占领的地块数量
    int citys = 0; // 占领的城市数量
    Point capitalPos = Point(-1, -1); // 首都位置

    Player(int playerID, Team* team): playerID(playerID), team(team) {}
};

struct Team {
    int teamID = 0;
    bool alive = true; // 队伍存活状态
    int units = 0; // 队伍总兵力数量
    int tiles = 0; // 队伍总占领地块数量
    int citys = 0; // 队伍总占领城市数量
    std::vector<std::shared_ptr<Player>> players; // 队伍中的玩家列表

    Team(int teamID): teamID(teamID) {}
};

class PlayerRegistry {
private:
    int playerCount = 0; // 玩家数量

    int teamCount = 0; // 队伍数量

    bool isRegisteredMoveQueue = true; // 是否已经注册移动队列

    std::vector<std::shared_ptr<Player>> players; // 全局玩家列表

    std::vector<std::shared_ptr<Team>> teams; // 全局队伍列表

    std::queue<std::shared_ptr<Player>> moveQueue; // 移动优先级队列
public:
    PlayerRegistry() = default;

    void registerPlayer(int playerID, int teamID); // 注册一个玩家 不构造 moveQueue

    void registerMoveQueue(); // 构造移动优先级队列

    const std::vector<std::shared_ptr<Player>>& getPlayers() const {
        return players;
    }

    const std::vector<std::shared_ptr<Team>>& getTeams() const {
        return teams;
    }

    const std::queue<std::shared_ptr<Player>>& getMoveQueue() const {
        return moveQueue;
    }

    void nextMoveQueue(); // 移动队列向后推迟 优先级最高的玩家变优先级最低

    bool isSameTeam(int playerID1, int playerID2) const; // 判断两个玩家是否属于同一队伍

    const std::shared_ptr<Player>& player(int playerID) const; // 获得该玩家

    const std::shared_ptr<Team>& team(int teamID) const; // 获得该小队
};

}