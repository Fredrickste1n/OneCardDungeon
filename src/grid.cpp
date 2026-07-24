#include <iostream>
#include <raylib.h>
#include "grid.h"
#include "tile.h"

Grid::Grid() {
    x = 0;
    y = 0;
    tileDim = 0;
    tileTypes = {{0}};

    SetTiles();
}

Grid::Grid(float xPos, float yPos, float tileDimensions, std::vector<std::vector<int>> tTPs) {
    x = xPos;
    y = yPos;
    tileDim = tileDimensions;
    tileTypes = tTPs;

    SetTiles();
}

void Grid::Draw() {
    for(int i = 0; i < tiles.size(); i++) {
        for(int j = 0; j < tiles[0].size(); j++) {
            Tile tile = tiles[i][j];
            DrawRectangle(tile.x, tile.y, tile.dim, tile.dim, tile.color);
        }
    }
}

void Grid::Update() {

}

void Grid::SetTiles() {
    for(int i = 0; i < tileTypes.size(); i++) {
        std::vector<Tile> column;
        for(int j = 0; j < tileTypes[0].size(); j++) {
            int tileType = tileTypes[j][i];
            Tile tile;
            if(tileType == 1) {
                tile = Tile{x + tileDim * i, y + tileDim * j, tileDim, true, false, false, PURPLE};
            } else if(tileType == 2) {
                tile = Tile{x + tileDim * i, y + tileDim * j, tileDim, false, true, false, PINK};
            } else if(tileType == 3){
                tile = Tile{x + tileDim * i, y + tileDim * j, tileDim, false, false, true, BLUE};
            } else {
                tile = Tile{x + tileDim * i, y + tileDim * j, tileDim, false, false, false, WHITE};
            }

            column.push_back(tile);
            
        }
        tiles.push_back(column);
    }
}

Vector2 Grid::FindAdventurerSpawn() {
    Vector2 pos = {0,0};

    for(int i = 0; i < tiles.size(); i++) {
        for(int j = 0; j < tiles[0].size(); j++) {
            Tile tile = tiles[i][j];
            if(tile.isPlayerSpawner) {
                pos = {tile.x, tile.y};
            }
        }
    }
    
    return pos;
}