#include "LabyrinthSquare.h"

LabyrinthSquare::LabyrinthSquare(const Vector2 coordinate)
{
    coordinate_ = coordinate;
}

Vector2 LabyrinthSquare::get_neighbour_coordinate(const direction dir) const
{
    auto coordinate = coordinate_;
    switch (dir)
    {
    case direction::up:
        coordinate.y++;
        break;
    case direction::down:
        coordinate.y--;
        break;
    case direction::left:
        coordinate.x--;
        break;
    case direction::right:
        coordinate.x++;
        break;
    }
    
    return coordinate;
}

bool LabyrinthSquare::operator==(const LabyrinthSquare& end) const
{
    return coordinate_.x == end.coordinate_.x && coordinate_.y == end.coordinate_.y;
}

float LabyrinthSquare::get_x() const
{
    return coordinate_.x;
}

float LabyrinthSquare::get_y() const
{
    return coordinate_.y;
}

Vector2 LabyrinthSquare::get_coordinate() const
{
    return coordinate_;
}
