#pragma once
#include "vector"

#include "LabyrinthSquare.h"

class LabyrinthGrid
{
public:
    explicit LabyrinthGrid(int size);
    
    LabyrinthSquare get_square(Vector2 coordinate) const;
    bool get_neighbour_square(LabyrinthSquare square, direction dir, LabyrinthSquare& result_square) const;
    
    void draw_labyrinth(int square_size, Vector2 offset);

    void create_labyrinth(bool add_noise);
    LabyrinthSquare* get_start() { return &squares_[start_index_]; }
    LabyrinthSquare* get_exit()  { return &squares_[exit_index_]; }
    const LabyrinthSquare& start_square() const { return squares_[start_index_]; }
    const LabyrinthSquare& exit_square()  const { return squares_[exit_index_]; }
    int get_square_size() const { return size_; }
    float distance_to_exit(LabyrinthSquare from) const;
private:
    bool is_valid_coordinate(Vector2 coordinate) const;
    bool is_coordinate_in_range(float i) const;
    bool get_weighted_next_square(const LabyrinthSquare& current, const LabyrinthSquare* previous,
                                  const LabyrinthSquare& end, LabyrinthSquare& result) const;
    int to_index(const LabyrinthSquare& square) const;

    std::vector<LabyrinthSquare> squares_;
    
    int size_;
    // LabyrinthGrid.h
    int start_index_ = 0;
    int exit_index_ = 0;
};
