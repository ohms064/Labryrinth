#pragma once
#include "cstdint"
#include "raylib.h"

enum class direction : uint8_t { up, down, left, right };

class LabyrinthSquare
{
public:
    LabyrinthSquare() : coordinate_{0, 0}, screen_position{0 , 0}
    {
    }

    explicit LabyrinthSquare(Vector2 coordinate);
    
    Vector2 get_neighbour_coordinate(direction dir) const;
    bool operator==(const LabyrinthSquare& end) const;

    bool obstacle = false;
    
    float get_x() const;
    float get_y() const;
    Vector2 get_coordinate() const;
    Vector2 screen_position;
    
private:
    Vector2 coordinate_; 
    
};
