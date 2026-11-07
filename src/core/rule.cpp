#include "rule.hpp"
#include "player.hpp"

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

void Rule::applyMove(GameMap &map, const PlayerRegistry &playerRegistry, const MoveOperation &op) {
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
            destTile.owner = sourceTile.owner;
        }
    }
    else {
        // 中立或不同队伍
        destTile.unit -= moveUnits;
        sourceTile.unit -= moveUnits;
        
    }
}

}