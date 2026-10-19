#pragma once

#include <format>
#include <raylib.h>
#include <vector>

#include "Character.h"
#include "LabyrinthGrid.h"

int main()
{
    constexpr int screen_width = 1280;
    constexpr int screen_height = 720;
    InitWindow(screen_width, screen_height, "Laberinto");

    SetTargetFPS(60);

    int PositionX = 20;
    int PositionY = 20;
    bool add_noise = false;
    
    auto offset = Vector2( 250, 10);

    LabyrinthGrid labyrinth_grid = LabyrinthGrid(8);
    Character character = Character(labyrinth_grid);
    
    labyrinth_grid.create_labyrinth(add_noise);
    character.initialize();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(SKYBLUE);
            labyrinth_grid.draw_labyrinth(80, offset);
            character.draw_character();
        
            if (IsKeyPressed(KEY_R))
            {
                labyrinth_grid.create_labyrinth(add_noise);
                character.initialize();
            }
            
            if (IsKeyPressed(KEY_N))
            {
                add_noise = !add_noise;
            }
                
            DrawText("Funciona!", PositionX, PositionY, 30, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
