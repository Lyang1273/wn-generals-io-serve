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

Tile& GameMap::at(const Point &p) {
    return at(p.x, p.y);
}

Tile GameMap::get(int x, int y) const {
    assert(isInside(x, y));
    return tiles[x * C + y];
}

Tile GameMap::get(const Point &p) const {
    return get(p.x, p.y);
}

void GameMap::set(int x, int y, const Tile &tile) {
    assert(isInside(x, y));
    tiles[x * C + y] = tile;
}

void GameMap::set(const Point &p, const Tile &tile) {
    set(p.x, p.y, tile);
}

bool GameMap::isInside(int x, int y) const {
    return x >= 0 && x < R && y >= 0 && y < C;
}

bool GameMap::isInside(const Point &p) const {
    return isInside(p.x, p.y);
}

Tile* GameMap::operator[](int x) {
    assert(x >= 0 && x < R);
    return &tiles[x * C];
}

}