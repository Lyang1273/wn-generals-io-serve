#include "player.hpp"
#include <algorithm>
#include "random.hpp"
#include "map.hpp"
#include <cassert>

namespace gen::core {

using std::vector;
using std::unique_ptr;
using std::queue;
using std::make_unique;
using std::move;

void PlayerRegistry::registerPlayer(int playerID, int teamID) {
    ++ playerCount;
    isRegisteredMoveQueue = false; // 注册玩家就要重新注册队列
    unique_ptr<Player> player = make_unique<Player>(playerID, teamID);
    bool hasTeam = false;
    for(auto &team : teams) {
        if(team->teamID == teamID) {
            team->players.push_back(playerID);
            players.push_back(move(player));
            hasTeam = true;
            break;
        }
    }
    if(!hasTeam) {
        ++ teamCount;
        unique_ptr<Team> team = make_unique<Team>(teamID);
        team->players.push_back(playerID);
        teams.push_back(move(team));
        players.push_back(move(player));
    }
}

void PlayerRegistry::registerMoveQueue() {
    isRegisteredMoveQueue = true; // 标记已经注册移动队列
    moveQueue = queue<Player*>(); // 清空队列
    shuffle(players.begin(), players.end(), rnd); // 随机打乱玩家顺序
    for(auto &player : players) {
        moveQueue.push(player.get());
    }
}

void PlayerRegistry::nextMoveQueue() {
    assert(isRegisteredMoveQueue); // 确定已经注册移动队列
    if(moveQueue.empty()) return;
    Player* player = moveQueue.front();
    moveQueue.pop();
    moveQueue.push(player);
}

bool PlayerRegistry::isSameTeam(int playerID1, int playerID2) const {
    if(playerID1 == NEUTRAL || playerID2 == NEUTRAL) return false; // 中立玩家不属于任何队伍
    int teamID1 = -1;
    int teamID2 = -1;
    for(auto &player : players) {
        if(player->playerID == playerID1) {
            teamID1 = player->teamID;
        }
        if(player->playerID == playerID2) {
            teamID2 = player->teamID;
        }
    }
    assert(teamID1 != -1 && teamID2 != -1); // 玩家不存在
    return teamID1 == teamID2;
}

Player* PlayerRegistry::atPlayer(int playerID) const {
    for(auto &player : players) {
        if(player->playerID == playerID) {
            return player.get();
        }
    }
    assert(false);
    return players[0].get();
}

Team* PlayerRegistry::atTeam(int teamID) const {
    for(auto &team : teams) {
        if(team->teamID == teamID) {
            return team.get();
        }
    }
    assert(false);
    return teams[0].get();
}

void PlayerRegistry::updatePlayerState(int playerID, int deltaUnits, int deltaTiles) {
    Player* player = atPlayer(playerID);
    Team* team = atTeam(player->teamID);
    player->units += deltaUnits;
    player->tiles += deltaTiles;
    team->units += deltaUnits;
    team->tiles += deltaTiles;
}

}