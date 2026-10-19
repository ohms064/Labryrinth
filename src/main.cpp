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

    int PositionX = 0;
    int PositionY = 20;
    
    bool add_noise = false;
    int grid_size = 8;
    int square_size = 80;
    
    auto offset = Vector2( 300, 10);

    LabyrinthGrid labyrinth_grid = LabyrinthGrid(grid_size);
    Character character = Character(labyrinth_grid);
    
    labyrinth_grid.create_labyrinth(add_noise);
    character.initialize();

    while (!WindowShouldClose())
    {
        
        if (IsKeyPressed(KEY_R))
        {
            labyrinth_grid.create_labyrinth(add_noise);
            character.initialize();
        }
            
        if (IsKeyPressed(KEY_N))
        {
            add_noise = !add_noise;
        }
            
        if (IsKeyPressed(KEY_RIGHT))
        {
            grid_size++;
            labyrinth_grid = LabyrinthGrid(grid_size);
            labyrinth_grid.create_labyrinth(add_noise);
            character.initialize();
        }
            
        if (IsKeyPressed(KEY_LEFT))
        {
            grid_size--;
            labyrinth_grid = LabyrinthGrid(grid_size);
            labyrinth_grid.create_labyrinth(add_noise);
            character.initialize();
        }
        
        if (IsKeyDown(KEY_UP))
        {
            square_size++;
        }
        
        if (IsKeyDown(KEY_DOWN))
        {
            square_size--;
            if (square_size < 0)
            {
                square_size = 0;
            }
        }
        
        BeginDrawing();
        {
            ClearBackground(SKYBLUE);
            labyrinth_grid.draw_labyrinth(square_size, offset);
            character.draw_character();
                
            DrawText("Arriba/abajo\nCambio de tamaño\nIzq/Der\nCambiar cuadrícula", PositionX, PositionY, 30, BLACK);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
