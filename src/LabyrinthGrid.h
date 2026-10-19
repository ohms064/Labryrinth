#pragma once
#include "vector"

#include "LabyrinthSquare.h"

class LabyrinthGrid
{
public:
    LabyrinthGrid(int size);
    
    LabyrinthSquare get_square(Vector2 coordinate) const;
    bool get_neighbour_square(LabyrinthSquare square, direction dir, LabyrinthSquare& result_square) const;
    
    void draw_labyrinth(int square_size_, Vector2 offset) const;
private:
    bool is_valid_coordinate(Vector2 coordinate) const;
    bool is_coordinate_in_range(float i) const;
    
    std::vector<LabyrinthSquare> squares_;
    int size_;
};
