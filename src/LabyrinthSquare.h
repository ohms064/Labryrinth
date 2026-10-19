#pragma once
#include "cstdint"
#include "raylib.h"

enum class direction : uint8_t { up, down, left, right };

class LabyrinthSquare
{
public:
    explicit LabyrinthSquare(Vector2 coordinate);
    
    Vector2 get_neighbour_coordinate(direction dir) const;
    bool operator==(const LabyrinthSquare& end) const;

    bool obstacle = false;
    
    float get_x() const;
    float get_y() const;
    
private:
    Vector2 coordinate_; 
    
};
