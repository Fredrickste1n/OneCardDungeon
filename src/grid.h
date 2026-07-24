#include <vector>
#include "tile.h"
#pragma once

class Grid {
public:
    float x, y;
    float tileDim;
    std::vector<std::vector<int>> tileTypes;
    std::vector<std::vector<Tile>> tiles;

    Grid();
    Grid(float, float, float, std::vector<std::vector<int>>);

    void Draw();
    void Update();
    void SetTiles();
    Vector2 FindAdventurerSpawn();
};