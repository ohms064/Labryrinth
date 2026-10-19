#pragma once
#include "LabyrinthGrid.h"
#include "LabyrinthSquare.h"

class Character
{
public:
    explicit Character(LabyrinthGrid& labyrinth_grid) : previous_square_(nullptr), current_square_(nullptr),
                                                        grid_(&labyrinth_grid)
    {
    }

    void initialize();
    
    void try_move();
    bool check_obstacle();
    void change_direction(direction new_direction);
    void turn(bool clockwise = true);
	float current_distance_to_exit() const;
    
    void draw_character() const;

private:
    LabyrinthSquare* previous_square_;
    LabyrinthSquare* current_square_;
    LabyrinthGrid* grid_;
    direction current_direction_ = direction::down;
};
