#include <raylib.h>
#pragma once

struct Tile {
    float x, y, dim;
    bool isWall, isSpawner, isPlayerSpawner;
    Color color;
};