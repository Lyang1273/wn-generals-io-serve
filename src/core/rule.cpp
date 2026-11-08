#include "rule.hpp"
#include "player.hpp"
#include <cassert>

namespace gen::core {

bool Rule::isValidMove(const GameMap &map, const MoveOperation &op) {
    if(op.d < 0 || op.d >= 4) return false; // 检查方向是否合法
    if(!map.isInside(op.source)) return false; // 检查源位置是否在地图内
    Point dest = calcDestination(op.source, op.d); // 计算目标位置
    if(!map.isInside(dest)) return false; // 检查目标位置是否在地图内
    const Tile& sourceTile = map.get(op.source);
    const Tile& destTile = map.get(dest);
    if(sourceTile.owner != op.playerID) return false; // 检查源位置的所有者是否是当前玩家
    if(sourceTile.unit <= 1) return false; // 源位置没有兵力或无法调动
    if(destTile.terrain == Terrain::Mountain) return false; // 目标位置是山地 无法移动
    return true;
}

void Rule::applyMove(GameMap &map, PlayerRegistry &playerRegistry, const MoveOperation &op) {
    if(!isValidMove(map, op)) return; // 无法移动
    Point dest = calcDestination(op.source, op.d); // 计算目标位置
    Tile& sourceTile = map.at(op.source);
    Tile& destTile = map.at(dest);
    int moveUnits = op.half ? (sourceTile.unit + 1) / 2 : sourceTile.unit - 1; // 计算移动的兵力 如果减半向上取整 相当于留下向下取整的兵力

    if(playerRegistry.isSameTeam(sourceTile.owner, destTile.owner)) {
        // 同一队伍
        destTile.unit += moveUnits; // 增加目标位置的兵力
        sourceTile.unit -= moveUnits; // 减少源位置的兵力
        if(destTile.terrain != Terrain::Capital) {
            // 不为首都则所有者变为源位置所有者
            playerRegistry.updatePlayerState(destTile.owner, -destTile.unit, -1);
            destTile.owner = sourceTile.owner;
            playerRegistry.updatePlayerState(sourceTile.owner, destTile.unit, 1);
        }
    }
    else {
        // 中立或不同队伍
        sourceTile.unit -= moveUnits;
        playerRegistry.updatePlayerState(sourceTile.owner, -moveUnits, 0);
        if(moveUnits <= destTile.unit) {
            // 打不过
            destTile.unit -= moveUnits;
            playerRegistry.updatePlayerState(destTile.owner, -moveUnits, 0);
        }
        else {
            // 打得过
            occupy(map, playerRegistry, destTile, sourceTile.owner, moveUnits);
        }
    }
}

void Rule::occupy(GameMap &map, PlayerRegistry &playerRegistry, Tile &destTile, int sourceID, int moveUnits) {
    assert(moveUnits > destTile.unit); // 打得过
    // 更新目标状态
    playerRegistry.updatePlayerState(destTile.owner, -destTile.unit, -1);
    destTile.owner = sourceID;
    destTile.unit = moveUnits - destTile.unit;
    playerRegistry.updatePlayerState(sourceID, destTile.unit, 1); // 加上目标格子
    if(destTile.terrain == Terrain::Capital) { // 是首都 击败该玩家
        destTile.terrain = Terrain::City;
        beatPlayer(map, playerRegistry, destTile.owner, sourceID);
        return;
    }
}

void Rule::beatPlayer(GameMap &map, PlayerRegistry &playerRegistry, int defeatenID, int sourceID) {
    playerRegistry.markNotAlive(defeatenID); // 记录不存活并且清空单位和地块
    int sumDeltaUnits = 0;
    int sumDeltaTiles = 0;
    for(auto &tile : map.atTiles()) {
        if(tile.owner == defeatenID) {
            tile.owner = sourceID; // 转换所有者
            if(tile.terrain != Terrain::Capital) {
                tile.unit /= 2; // 非首都保留一半
            }
            sumDeltaUnits += tile.unit;
            ++ sumDeltaTiles;
            if(tile.terrain == Terrain::Capital) {
                // 在外面已经处理过了 理论上不执行
                // 将敌方首都转换为自己的城市
                tile.terrain = Terrain::City;
            }
        }
    }
    playerRegistry.updatePlayerState(sourceID, sumDeltaUnits, sumDeltaTiles);
    // 加上单位和地块
}

}