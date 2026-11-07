#include "map.hpp"
#include <cassert>

namespace gen::core {

GameMap::GameMap(int R, int C): R(R), C(C) {
    tiles.resize(R * C, Tile());
}

Tile& GameMap::at(int x, int y) {
    assert(isInside(x, y));
    return tiles[x * C + y];
}

Tile GameMap::get(int x, int y) const {
    assert(isInside(x, y));
    return tiles[x * C + y];
}

void GameMap::set(int x, int y, const Tile &tile) {
    assert(isInside(x, y));
    tiles[x * C + y] = tile;
}

bool GameMap::isInside(int x, int y) const {
    return x >= 0 && x < R && y >= 0 && y < C;
}

}