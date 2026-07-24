#include <iostream>
#include <raylib.h>
#include "adventurer.h"
#include "grid.h"
#include "maps.h"

using namespace std;
using namespace Maps;

const float tileSize = 128;

bool gameStart = false;
bool playerTurn, enemyTurn = false;
bool moveMode, attackMode = false;

char* gamePhase = "main menu";


int main() 
{
    cout << "starting" << endl;
    InitWindow(0, 0, "One Card Dungeon");
    ToggleFullscreen();

    // Sets window to monitor specs
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    float gridPixelWidth = tileSize * 5;
    float gridPixelHeight = tileSize * 5;

    float gridX = (GetScreenWidth() - gridPixelWidth) / 2.0f;
    float gridY = (GetScreenHeight() - gridPixelHeight) / 2.0f;

    // Sets constant game speed
    SetTargetFPS(60);

    // Creating maps
    Grid one = {gridX, gridY, tileSize, levelOne};

    Grid currentLevel = one;

    // Creating Adventurer
    Adventurer adventurer(one.FindAdventurerSpawn(), tileSize, currentLevel);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
// UPDATING
//------------------------------------------------------------------------------------------
        if(gameStart) {
            if(playerTurn) {
                if(moveMode) {
                    adventurer.Update();
                    gamePhase = "player: move mode";
                    if(IsKeyPressed(KEY_SPACE)) {
                        moveMode = false;
                        attackMode = true;
                    }
                } else if(attackMode) {
                    gamePhase = "player: attack mode";
                    if(IsKeyPressed(KEY_SPACE)) {
                        attackMode = false;
                        playerTurn = false;
                        enemyTurn = true;
                    }
                }
            } else if(enemyTurn) {
                gamePhase = "enemy: move/attack phase";
                if(IsKeyPressed(KEY_SPACE)) {
                    enemyTurn = false;
                }
            }
        } else if(!gameStart) {
            gamePhase = "main menu";
            if(IsKeyPressed(KEY_SPACE)) {
                gameStart = true;
                playerTurn = true;
                moveMode = true;
            }
        }
        

// DRAWING
//------------------------------------------------------------------------------------------
        ClearBackground(BLACK);

        if(gameStart) {
            one.Draw();
            adventurer.Draw();

            // Draw adventurer stats
            DrawText("Adventurer stats", 60, 250, 20, RED);
            DrawText(TextFormat("%i", adventurer.speedStat), 60, 300, 20, RED);
            DrawText(TextFormat("%i", adventurer.attackStat), 110, 300, 20, RED);
            DrawText(TextFormat("%i", adventurer.defenseStat), 160, 300, 20, RED);
            DrawText(TextFormat("%i", adventurer.rangeStat), 210, 300, 20, RED);
        }

        DrawText(TextFormat("%s", gamePhase), 0, 100, 30, WHITE);

        EndDrawing();
    }
    
    CloseWindow();
}