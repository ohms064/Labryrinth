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

    void create_labyrinth(bool add_noise);
private:
    bool is_valid_coordinate(Vector2 coordinate) const;
    bool is_coordinate_in_range(float i) const;
    bool get_weighted_next_square(const LabyrinthSquare& current, const LabyrinthSquare* previous,
                                  const LabyrinthSquare& end, LabyrinthSquare& result) const;
    int to_index(const LabyrinthSquare& square) const;

    std::vector<LabyrinthSquare> squares_;
    int size_;
    
    LabyrinthSquare start_;
    LabyrinthSquare exit_;
};
