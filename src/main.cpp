#pragma once

#include <format>
#include <raylib.h>
#include <vector>

#include "LabyrinthGrid.h"

int main()
{
    constexpr int screen_width = 1280;
    constexpr int screen_height = 720;
    InitWindow(screen_width, screen_height, "Laberinto");

    SetTargetFPS(60);

    int PositionX = 20;
    int PositionY = 20;
    
    auto offset = Vector2( 250, 10);

    LabyrinthGrid labyrinth_grid = LabyrinthGrid(8);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(SKYBLUE);
        
            labyrinth_grid.draw_labyrinth(80, offset);
                
            DrawText("Funciona!", PositionX, PositionY, 30, BLACK);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
