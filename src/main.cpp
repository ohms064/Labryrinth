#pragma once

#include <format>
#include <raylib.h>
#include <vector>

int main()
{
    constexpr int screen_width = 1280;
    constexpr int screen_height = 720;
    InitWindow(screen_width, screen_height, "Laberinto");

    SetTargetFPS(60);

    int PositionX = 20;
    int PositionY = 20;
    
    int frame_count = 0;
    
    
    Camera2D camera = { 0 };
    camera.rotation = 0.0f;
    camera.offset = Vector2 { screen_width/2.0f, screen_height/2.0f };
    camera.zoom = 1.0f;


    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(SKYBLUE);
                
            DrawText("Funciona!", PositionX, PositionY, 30, BLACK);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
