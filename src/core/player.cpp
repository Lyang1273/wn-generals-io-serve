#include "player.hpp"
#include <algorithm>
#include "random.hpp"
#include "map.hpp"
#include <cassert>

namespace gen::core {
    using std::vector;
    using std::shared_ptr;
    using std::queue;
    using std::make_shared;

    void PlayerRegistry::registerPlayer(int playerID, int teamID) {
        ++ playerCount;
        isRegisteredMoveQueue = false; // 注册玩家就要重新注册队列
        bool hasTeam = false;
        for(auto &team : teams) {
            if(team->teamID == teamID) {
                shared_ptr<Player> player = make_shared<Player>(playerID, team.get());
                team->players.push_back(player);
                players.push_back(player);
                hasTeam = true;
                break;
            }
        }
        if(!hasTeam) {
            ++ teamCount;
            shared_ptr<Team> team = make_shared<Team>(teamID);
            shared_ptr<Player> player = make_shared<Player>(playerID, team.get());
            team->players.push_back(player);
            teams.push_back(team);
            players.push_back(player);
        }
    }

    void PlayerRegistry::registerMoveQueue() {
        isRegisteredMoveQueue = true; // 标记已经注册移动队列
        moveQueue = queue<shared_ptr<Player>>(); // 清空队列
        shuffle(players.begin(), players.end(), rnd); // 随机打乱玩家顺序
        for(auto &player : players) {
            moveQueue.push(player);
        }
    }

    void PlayerRegistry::nextMoveQueue() {
        assert(isRegisteredMoveQueue); // 确定已经注册移动队列
        if(moveQueue.empty()) return;
        shared_ptr<Player> player = moveQueue.front();
        moveQueue.pop();
        moveQueue.push(player);
    }

    bool PlayerRegistry::isSameTeam(int playerID1, int playerID2) const {
        if(playerID1 == NEUTRAL || playerID2 == NEUTRAL) return false; // 中立玩家不属于任何队伍
        int teamID1 = -1;
        int teamID2 = -1;
        for(auto &player : players) {
            if(player->playerID == playerID1) {
                teamID1 = player->team->teamID;
            }
            if(player->playerID == playerID2) {
                teamID2 = player->team->teamID;
            }
        }
        assert(teamID1 != -1 && teamID2 != -1); // 玩家不存在
        return teamID1 == teamID2;
    }

    const shared_ptr<Player>& PlayerRegistry::player(int playerID) const {
        for(auto &player : players) {
            if(player->playerID == playerID) {
                return player;
            }
        }
        assert(false);
        return players[0];
    }

    const shared_ptr<Team>& PlayerRegistry::team(int teamID) const {
        for(auto &team : teams) {
            if(team->teamID == teamID) {
                return team;
            }
        }
        assert(false);
        return teams[0];
    }
}