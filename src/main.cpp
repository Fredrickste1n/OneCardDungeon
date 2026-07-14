#include <raylib.h>

int main() 
{
    
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            ClearBackground(BLACK);

        EndDrawing();
    }
    
    CloseWindow();
}