#include "LabyrinthGrid.h"
#include <cmath>
#include <iostream>

LabyrinthGrid::LabyrinthGrid(int size)
{
    size_ = size;
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            auto square = LabyrinthSquare(Vector2(x, y));
            squares_.push_back(square);
            std::cout << "index:" << x + y << " x: " << square.get_x() << " y: " << square.get_y() << '\n';
        }
    }
}

LabyrinthSquare LabyrinthGrid::get_square(Vector2 coordinate) const
{
    return squares_[coordinate.x * size_ + coordinate.y];
}

bool LabyrinthGrid::get_neighbour_square(LabyrinthSquare square, direction dir, LabyrinthSquare& result_square) const
{
    auto coordinate = square.get_neighbour_coordinate(dir);
    if (!is_valid_coordinate(coordinate))
    {
        result_square = square;
        return false;
    }
    
    result_square = get_square(coordinate);
    return true;
}

void LabyrinthGrid::draw_labyrinth(int square_size_, Vector2 offset) const
{
    for (const auto& square : squares_)
    {
        const int mod_y = std::fmod(square.get_y(), 2.f);
        DrawRectangle(offset.x + (square_size_ * square.get_x()), offset.y + (square_size_ * square.get_y()),
            square_size_, square_size_, std::fmod(square.get_x() + mod_y, 2) == 0 ? BLACK : WHITE);
    }
}

bool LabyrinthGrid::is_valid_coordinate(const Vector2 coordinate) const
{
    return is_coordinate_in_range(coordinate.x) && is_coordinate_in_range(coordinate.y);
}

bool LabyrinthGrid::is_coordinate_in_range(const float i) const
{
    return i > 0 && i < size_;
}
