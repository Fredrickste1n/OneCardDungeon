#include <iostream>
#include "grid.h"

#pragma once

class Adventurer {
public:
    float x, y, dim;
    int health;
    int speedStat, attackStat, defenseStat, rangeStat;
    int speedEnergy, attackEnergy, defenseEnergy;
    int speedUsed;
    Vector2 startPos;
    Grid currentLevel;

    Adventurer(Vector2, float, Grid);

    void Draw();
    void Update();
    void GetSpeedUsed();
    bool IsSpawnDiag();
    bool IsWallAdj();
    void Move();
    Vector2 GetCurrentTile();
};