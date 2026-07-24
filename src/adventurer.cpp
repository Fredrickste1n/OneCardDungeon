#include <iostream>
#include <cmath>
#include <raylib.h>
#include "adventurer.h"
#include "grid.h"
#include "tile.h"

Adventurer::Adventurer(Vector2 pos, float dimensions, Grid curLvl) {
    x = pos.x;
    y = pos.y;
    dim = dimensions;

    health = 6;

    speedStat = 10000;
    attackStat = 1;
    defenseStat = 1;
    rangeStat = 2;

    speedEnergy = 0;
    attackEnergy = 0;
    defenseEnergy = 0;

    speedUsed = 0;
    currentLevel = curLvl;
    startPos = GetCurrentTile();

}

void Adventurer::Draw() {
    DrawRectangle(x, y, dim, dim, GREEN);
    DrawText(TextFormat("%i", health), x + dim / 2, y + dim / 2, 35, BLACK);
    DrawText(TextFormat("%i", speedUsed), 10, 10, 60, WHITE);
}

void Adventurer::Update() {
    Move();
    
    speedEnergy = speedStat - speedUsed;
}

void Adventurer::Move() {
    Vector2 pos = GetCurrentTile();

    // Cardinal directions
    if(IsKeyPressed(KEY_W) && pos.y > 0 && speedEnergy >= 2) {
        if(!currentLevel.tiles[pos.x][pos.y - 1].isWall) {
            y -= dim;
            speedUsed += 2;
        }
    }

    if(IsKeyPressed(KEY_S) && pos.y < currentLevel.tiles[0].size() - 1 && speedEnergy >= 2) {
        if(!currentLevel.tiles[pos.x][pos.y + 1].isWall) {
            y += dim;
            speedUsed += 2;
        }
    }

    if(IsKeyPressed(KEY_A) && pos.x > 0 && speedEnergy >= 2) {
        if(!currentLevel.tiles[pos.x - 1][pos.y].isWall) {
            x -= dim;
            speedUsed += 2;
        }
    }

    if(IsKeyPressed(KEY_D) && pos.x < currentLevel.tiles.size() - 1 && speedEnergy >= 2) {
        if(!currentLevel.tiles[pos.x + 1][pos.y].isWall) {
            x += dim;
            speedUsed += 2;
        }
    }


    // Diagonal directions
    if(IsKeyPressed(KEY_E) && pos.y > 0 && pos.x < currentLevel.tiles.size() && speedEnergy >= 3) {
        if(!currentLevel.tiles[pos.x + 1][pos.y - 1].isWall) {
            y -= dim;
            x += dim;
            speedUsed += 3;
        }
    }

    if(IsKeyPressed(KEY_Q) && pos.y > 0 && pos.x > 0 && speedEnergy >= 3) {
        if(!currentLevel.tiles[pos.x - 1][pos.y - 1].isWall) {
            y -= dim;
            x -= dim;
            speedUsed += 3;
        }
    }

    if(IsKeyPressed(KEY_Z) && pos.y < currentLevel.tiles[0].size() - 1 && pos.x > 0 && speedEnergy >= 3) {
        if(!currentLevel.tiles[pos.x - 1][pos.y + 1].isWall) {
            y += dim;
            x -= dim;
            speedUsed += 3;
        }
    }

    if(IsKeyPressed(KEY_C) && pos.y < currentLevel.tiles[0].size() - 1 && pos.x < currentLevel.tiles.size() && speedEnergy >= 3) {
        if(!currentLevel.tiles[pos.x + 1][pos.y + 1].isWall) {
            y += dim;
            x += dim;
            speedUsed += 3;
        }
    }
}

Vector2 Adventurer::GetCurrentTile() {
    Vector2 currentTile = {0, 0};

    Rectangle adventurerRec = {x, y, dim, dim};

    for(int i = 0; i < currentLevel.tiles.size(); i++) {
        for (int j = 0; j < currentLevel.tiles[0].size(); j++) {
            Tile tile = currentLevel.tiles[i][j];
            Vector2 tilePoint = {tile.x + tile.dim / 2, tile.y + tile.dim / 2};
            if(CheckCollisionPointRec(tilePoint, adventurerRec)) {
                currentTile = {(float)i, (float)j};
            }
        }
    }

    return currentTile;
}

void Adventurer::GetSpeedUsed() {
    speedUsed = 0;
    Vector2 pos = GetCurrentTile();
    int xDiff = std::abs(pos.x - startPos.x);
    int yDiff = std::abs(pos.y - startPos.y);

    if(yDiff == 0) {
        speedUsed += xDiff * 2;
    } else if(xDiff == 0) {
        speedUsed += yDiff * 2;
    } else if(xDiff > yDiff){
        speedUsed += (xDiff * 2) + (yDiff); 
    } else if(yDiff > xDiff){
        speedUsed += (yDiff * 2) + (xDiff); 
    } else if(xDiff == yDiff && xDiff != 0) {
        speedUsed += (xDiff * 2) + (yDiff);
    }

    if(IsWallAdj()) {
        speedUsed++;
    }
}

bool Adventurer::IsSpawnDiag() {
    Vector2 pos = GetCurrentTile();
    int xDiff = std::abs(pos.x - startPos.x);
    int yDiff = std::abs(pos.y - startPos.y);

    if(xDiff == yDiff && xDiff != 0) {
        return true;
    } else {
        return false;
    }
}

bool Adventurer::IsWallAdj() {
    if(IsSpawnDiag()) {
        Vector2 pos = GetCurrentTile();
        int xDiff = pos.x - startPos.x;
        int yDiff = pos.y - startPos.y;

        int gridSize = currentLevel.tiles.size() - 1;

        for(int i = 1; i < currentLevel.tiles.size(); i++) {
            if(xDiff > 0) {
                if(currentLevel.tiles[i][gridSize - i].isWall) {
                    return true;
                }
            } else if(xDiff < 0) {
                if(currentLevel.tiles[gridSize - i][gridSize - i].isWall) {
                    return true;
                }
            }
        }
    }

    return false;
}